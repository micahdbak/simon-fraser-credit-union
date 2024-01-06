import socket

def network_custom(custom_network_message):
    #Create a UDP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    try:
        #Set up server address
        server_address = ("204.83.169.199", 25543)
        
        #Send a message to the server
        client_socket.sendto(custom_network_message.encode(), server_address)

        #Receive the response from the server
        buffer, _ = client_socket.recvfrom(1024)
        received_data = buffer.decode()

        #Process received data
        return received_data

    except Exception as e:
        #Handle exceptions, socket creation error or no response from the server
        print(f"Error: {str(e)}")
        return f"Error: {str(e)}"

    finally:
        #Close the socket
        client_socket.close()

#Check how many unread packets are stored in the server
def network_check(network_id):
    return network_custom(f"check\n{network_id}")

#recived oldest unchecked packet
def network_request(network_id):
    return network_custom(f"request\n{network_id}")

#Used to check if the server is online
def network_status():
    return network_custom("status")
#request server time (mainly for client & server to calibrate timezone differneces)
def network_time():
    return network_custom("time")