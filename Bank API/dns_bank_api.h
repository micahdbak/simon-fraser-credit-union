//this
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DNS_BANK_API

    char* dns_bank_custom(const char* custom_bank_message) {
        //Create a UDP socket
        int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (clientSocket == -1) {
            fprintf(stderr, "Error creating socket\n");
            return strdup("Error: Could Not Make A Socket To Contact Server With");
        }

        //Set up server address
        struct sockaddr_in serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); // Server's IP address
        serverAddress.sin_port = htons(25544); //Server's Port

        //Send a message to the server
        sendto(clientSocket, custom_bank_message, strlen(custom_bank_message), 0,
               (struct sockaddr*)&serverAddress, sizeof(serverAddress));

        char* buffer = (char*)malloc(1025); //Buffer with space for null terminator

        //Receive the response from the server
        ssize_t receivedBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);
        if (receivedBytes == -1) {
            fprintf(stderr, "Error receiving data.\n");
            close(clientSocket);
            free(buffer);
            return strdup("Error: No Response From Server.");
        }

        //Process received data
        buffer[receivedBytes] = '\0';

        //Close the socket
        close(clientSocket);
        return buffer;
    }

    //Subjects: NAME, CODE, PASS
    char* dns_bank_verify(const char* account_id, const char* subject, const char* first_arg, const char* second_arg) {
        //Calculate the length of the message
	    size_t message_len = strlen("verify\n") + strlen(account_id) + strlen(subject) + strlen(first_arg) + strlen(second_arg) + 4;

	    //Allocate memory for the message
	    char* message = (char*)malloc(message_len);

	    //Check for allocation failure
	    if (message == NULL) {
	        //Handle memory allocation failure
	        return NULL;
	    }

	    //Use snprintf to format the string
	    snprintf(message, message_len, "verify\n%s\n%s\n%s\n%s\n", account_id, subject, first_arg, second_arg);

	    //Rest of the function

	    return message;
    }

    char* dns_bank_transfer(const char* account_from, const char* account_to, const char* secure_code, const char* amount) {
        //Calculate the length of the message
	    size_t message_len = strlen("transfer\n") + strlen(account_from) + strlen(account_to) + strlen(secure_code) + strlen(amount) + 4;

	    //Allocate memory for the message
	    char* message = (char*)malloc(message_len);

	    //Check for allocation failure
	    if (message == NULL) {
	        //Handle memory allocation failure
	        return NULL;
	    }

	    //Use snprintf to format the string
	    snprintf(message, message_len, "transfer\n%s\n%s\n%s\n%s\n", account_from, secure_code, amount, account_to);

	    //Rest of the function

	    return message;
    }

    char* dns_bank_get_info(const char* account_id) {
        char* message = (char*)malloc(strlen("account_info\n") + strlen(account_id) + 2);
        sprintf(message, "account_info\n%s", account_id);
        char* result = dns_bank_custom(message);
        free(message);
        return result;
    }

    char* dns_bank_status() {
        return dns_bank_custom("status");
    }

    char* dns_bank_time() {
        return dns_bank_custom("time");
    }