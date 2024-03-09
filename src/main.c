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

            printf(
                "Request %d of %d:\n\tCard Data: %s\n\tPrice: %s\n\tVendor: %s\n",
                i + 1,
                n,
                card_data + 1,
                price_str + 1,
                vendor + 1
            );
        }

        printf("Done.\n");
        sleep(NETWORK_CHECK_INTERVAL);
    }

    return 0; // success
}
