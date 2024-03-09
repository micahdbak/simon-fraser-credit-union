//this
#include <stdio.h>
#include <stdlib.h>
#include "dns_bank_api.h"

int main() {
    //Example usage
    char* result = dns_bank_transfer("13513780037206503511", "15406478860434420512", "3156077800", "100");
    printf("%s\n", result);
    free(result);
    return 0;
}
