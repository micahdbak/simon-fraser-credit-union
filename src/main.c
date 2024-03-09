#include "dns_bank_api.h"
#include "dns_network_api.h"

#include <stdio.h>

int main(int argc, char **argv) {
    printf("Starting the SFCU...\n");

    char *bank_api_status = dns_bank_status();
    char *network_api_status = dns_network_status();

    printf("dns_bank_status()\n\t%s\ndns_network_status()\n\t%s\n", bank_api_status, network_api_status);

    free(bank_api_status);
    free(network_api_status);

    return 0; // success
}
