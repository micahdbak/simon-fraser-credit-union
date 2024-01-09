//this
#include <stdio.h>
#include <stdlib.h>
#include "dns_bank_api.h"

int main() {
    //Example usage
    char* result = dns_bank_status();
    printf("%s\n", result);
    free(result);
    return 0;
}
