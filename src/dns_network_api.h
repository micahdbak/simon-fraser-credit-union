#ifndef DNS_NETWORK_API_H
#define DNS_NETWORK_API_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char * dns_network_custom(const char* custom_network_message) {
    //Create a UDP socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return "Error: Could Not Make A Socket To Contact Server With";
    }

    //Set up server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); //Server's IP address
    serverAddress.sin_port = htons(25542); //Server's Port

    //Send a message to the server
    sendto(clientSocket, custom_network_message, strlen(custom_network_message), 0,
           (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char * buffer = (char *)malloc(1024*sizeof(char));

    //Receive the response from the server
    ssize_t receivedBytes = recvfrom(clientSocket, buffer, 1024*sizeof(char), 0, NULL, NULL);
    if (receivedBytes == -1) {
        perror("Error receiving data.");
        close(clientSocket);
        free(buffer);
        return "Error: No Responce From Server.";
    }

    //Process received data
    buffer[receivedBytes] = '\0';

    //Close the socket
    close(clientSocket);
    return buffer;
}

//Check how many unread packets are stored in the server
char * dns_network_check(const char* network_id) {
    char custom_message[1024];
    snprintf(custom_message, sizeof(custom_message), "check\n%s", network_id);
    return dns_network_custom(custom_message);
}

//recived oldest unchecked packet
char * dns_network_request(const char* network_id) {
    char custom_message[1024];
    snprintf(custom_message, sizeof(custom_message), "request\n%s", network_id);
    return dns_network_custom(custom_message);
}

//Used to check if the Server is Online
char * dns_network_status() {
    return dns_network_custom("status");
}

//request server time (mainly for client & server to calibrate timezone differneces)
char * dns_network_time() {
    return dns_network_custom("time");
}

#endif
