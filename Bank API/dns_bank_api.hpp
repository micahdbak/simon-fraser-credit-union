#define DNS_BANK_API

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace dns {

	std::string bank_custom(std::string custom_bank_message) {
		
	    //Create a UDP socket
	    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	    if (clientSocket == -1) {
	        std::cerr << "Error creating socket" << std::endl;
	        return "Error: Could Not Make A Socket To Contact Server With";
	    }

	    //Set up server address
	    struct sockaddr_in serverAddress;
	    std::memset(&serverAddress, 0, sizeof(serverAddress));
	    serverAddress.sin_family = AF_INET;
	    serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); //Server's IP address
	    serverAddress.sin_port = htons(25544); //Server's Port

	    //Send a message to the server
	    sendto(clientSocket, custom_bank_message.c_str(), custom_bank_message.length(), 0,
	           (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	    char buffer[1024];

	    //Receive the response from the server
	    ssize_t receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
	    if (receivedBytes == -1) {
	        std::cerr << "Error receiving data." << std::endl;
	        close(clientSocket);
	        return "Error: No Responce From Server.";
	    }

	    //Process received data
	    buffer[receivedBytes] = '\0';

	    //Close the socket
	    close(clientSocket);
	    return buffer;
	}


	//Subjects: NAME, CODE, PASS
	std::string bank_verify(std::string account_id, std::string subject, std::string first_arg, std::string second_arg = "") {
		return bank_custom("verify\n"+account_id+"\n"+subject+"\n"+first_arg+"\n"+second_arg);
	}

	std::string bank_transfer(std::string account_from, std::string account_to, std::string secure_code, std::string amount) {
		return bank_custom("transfer\n"+account_from+"\n"+secure_code+"\n"+amount+"\n"+account_to);
	}

	std::string bank_get_info(std::string account_id) {
		return bank_custom("account_info\n"+account_id);
	}

	std::string bank_status() {
		return bank_custom("status");
	}

	std::string bank_time() {
		return bank_custom("time");
	}

}
