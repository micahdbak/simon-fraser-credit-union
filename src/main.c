#include "dns_bank_api.h"
#include "dns_network_api.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// number of seconds between every network check
#define NETWORK_CHECK_INTERVAL  5

// arbitrary maximum length of a character array
#define ARBMAX  1024

// the psql command to run an SQL query
#define PSQL_QUERY_BEGIN         "psql -d sfcu -c \"COPY ("
#define PSQL_QUERY_BEGIN_SIMPLE  "psql -d sfcu -c \""
#define PSQL_QUERY_END           ") TO '/tmp/sfcu.csv' WITH CSV DELIMITER ','\""
#define PSQL_QUERY_END_SIMPLE    "\""

#define CREDIT_FEE  0.05 // we keep 5% of every credit transaction made

// these are hard coded; don't steal money from us pls :(((
#define sfcu_account_from  "743181187701964104"
#define sfcu_secure_code   "3532964684"

int get_account_info(const char *account_id, unsigned long int *bank_id, unsigned long int *bank_code) {
    char psql_query[ARBMAX];

    snprintf(
        psql_query,
        ARBMAX,
        PSQL_QUERY_BEGIN
            "SELECT (bank_id, bank_code) FROM accounts WHERE id='%s' LIMIT 1"
        PSQL_QUERY_END,
        account_id
    );

    int ret = system(psql_query);

    if (ret != 0) {
        *bank_id = 0;
        *bank_code = 0;
        return ret;
    }

    FILE *sfcucsv = fopen("/tmp/sfcu.csv", "r");

    if (sfcucsv == NULL) {
        printf("Couldn't open /tmp/sfcu.csv.\n");
        return -1;
    }

    fscanf(sfcucsv, "\"(%lu,%lu)\"", bank_id, bank_code);
    fclose(sfcucsv);

    return 0;
}

int insert_request(const char *account_from, const char *account_to, const char *amount, const char *is_credit) {
    char psql_query[ARBMAX];

    snprintf(
        psql_query,
        ARBMAX,
        PSQL_QUERY_BEGIN_SIMPLE
            "INSERT INTO requests (from_id, to_id, amount, is_credit) VALUES ('%s', '%s', '%s', %s)"
        PSQL_QUERY_END_SIMPLE,
        account_from,
        account_to,
        amount,
        is_credit
    );

    return system(psql_query);
}

int main(int argc, char **argv) {
    printf("Starting the SFCU...\n");

    // get DNS server statuses

    char *bank_status = dns_bank_status();
    char *network_status = dns_network_status();

    printf("dns_bank_status()\n\t%s\ndns_network_status()\n\t%s\n", bank_status, network_status);

    free(bank_status);
    free(network_status);

    printf("Starting the main loop...\n");

    // run main loop

    while (true) {
        // 104 is the network ID for SFCU
        char *network_check = dns_network_check("104");
        int n;
        sscanf(network_check, "Check: 104: %d\n", &n);
        free(network_check); // be memory-safe!

        if (n == 0) {
            // don't clutter stdout if there's no requests; just wait
            sleep(NETWORK_CHECK_INTERVAL);
            continue;
        }

        printf("----\nGot %d unchecked requests.\n", n);

        for (int i = 0; i < n; i++) {
            char *network_request = dns_network_request("104");
            char card_data[ARBMAX], price_str[ARBMAX], vendor[ARBMAX], time[ARBMAX];
            bool is_credit = false;
            sscanf(
                network_request,
                "Card Data: %s\nPrice: %s\nVendor: %s\nTime: %s\n",
                card_data,
                price_str,
                vendor,
                time
            );
            printf("%s\n", network_request);
            free(network_request); // be memory-safe!

            // these end with '}'; trim short by one character
            card_data[strlen(card_data) - 1] = '\0';
            price_str[strlen(price_str) - 1] = '\0';
            vendor[strlen(vendor) - 1] = '\0';
            // NOTE: use str + 1, as each starts with '{'

            // determine credit payment by a preceding 'c' in the vendor ID
            if (vendor[1] == 'c') {
                is_credit = true;
                printf("Detected credit transaction!\n");
            }

            printf(
                "Request %d of %d:\n\tCard Data: %s\n\tPrice: %s\n\tVendor: %s\n",
                i + 1,
                n,
                card_data + 1,
                price_str + 1,
                is_credit ? vendor + 2 : vendor + 1
            );

            insert_request(card_data + 1, is_credit ? vendor + 2 : vendor + 1, price_str + 1, is_credit ? "'t'" : "'f'");

            // get account info for sender
            unsigned long int sender_bank_id, sender_bank_code;
            int sender_ret = get_account_info(card_data + 1, &sender_bank_id, &sender_bank_code);
            if (sender_ret != 0) {
                continue;
            }

            // get account info for recipient
            unsigned long int rec_bank_id, rec_bank_code;
            int rec_ret = get_account_info(is_credit ? vendor + 2 : vendor + 1, &rec_bank_id, &rec_bank_code);
            if (rec_ret != 0) {
                continue;
            }

            char account_from[ARBMAX], account_to[ARBMAX], secure_code[ARBMAX];

            sprintf(account_from, "%lu", sender_bank_id);
            sprintf(account_to, "%lu", rec_bank_id);
            sprintf(secure_code, "%lu", sender_bank_code);

            if (is_credit) {
                double amount = strtod(price_str + 1, NULL), fee = amount * CREDIT_FEE;
                amount -= fee;
                // write amount minus percent charge to price_str to 10 decimal places of accuracy
                sprintf(price_str + 1, "%.10f", amount);
                printf("Credit transaction detected; we are charging a %.10f fee (%f).\n", fee, CREDIT_FEE);
            }

            char *dns_response = dns_bank_transfer(
                is_credit ? sfcu_account_from : account_from,
                account_to,
                is_credit ? sfcu_secure_code : secure_code,
                price_str + 1
            );
            printf("%s\n", dns_response); // print DNS server response

            dns_response = dns_bank_get_info(account_from);
            printf("Sender: %s\n", dns_response);
            dns_response = dns_bank_get_info(account_to);
            printf("Recipient: %s\n", dns_response);

            free(dns_response); // be memory safe!!
        }

        printf("Done.\n");
        sleep(NETWORK_CHECK_INTERVAL);
    }

    return 0; // success
}
