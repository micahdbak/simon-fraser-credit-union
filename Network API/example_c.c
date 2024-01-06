#include <stdio.h>
#include <stdlib.h>
#include "dns_network_api.h"

int main() {
    //Example usage
    char* result = dns_network_check("888");
    printf("%s\n", result);
    free(result);
    return 0;
}