#include "dns_bank_api.h"
#include "dns_network_api.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// number of seconds between every network check
#define NETWORK_CHECK_INTERVAL  10

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
        printf("----\n"); // divider
        // 104 is the network ID for SFCU
        char *network_check = dns_network_check("104");
        int n;
        sscanf(network_check, "Check: 104: %d\n", &n);
        free(network_check); // be memory-safe!
        printf("Got %d unchecked requests.\n", n);

        for (int i = 0; i < n; i++) {
            printf("\tReceiving request %d of %d...\n", i, n);
            char *network_request = dns_network_request("104");
            // handle the unchecked request:
            // - parse who the vendor is; check against database for dns bank id
            // - parse who the purchaser is; check against database for dns bank id
            // - incur debt internally to purchaser; send transfer to vendor from SFCU dns bank account
            free(network_request);
        }

        printf("Done checking requests; waiting %d seconds before trying again.\n", NETWORK_CHECK_INTERVAL);
        sleep(NETWORK_CHECK_INTERVAL);
    }

    return 0; // success
}
