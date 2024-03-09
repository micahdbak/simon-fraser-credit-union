import socket

def bank_custom(custom_bank_message: str):
    #Create a UDP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        #Set up server address
        server_address = ("204.83.169.199", 25544)

        #Send a message to the server
        client_socket.sendto(custom_bank_message.encode(), server_address)

        #Receive the response from the server
        buffer, _ = client_socket.recvfrom(1024)

        #Process received data
        response = buffer.decode()

    except socket.error as e:
        print(f"Error: {e}")
        response = "Error: No Response From Server."

    finally:
        #Close the socket
        client_socket.close()

    return response

def bank_verify(account_id: str, subject: str, first_arg: str, second_arg=""):
    message = f"verify\n{account_id}\n{subject}\n{first_arg}\n{second_arg}"
    return bank_custom(message)

def bank_transfer(account_from:str, account_to:str, secure_code: str, amount: str):
    message = f"transfer\n{account_from}\n{secure_code}\n{amount}\n{account_to}"
    return bank_custom(message)

def bank_get_info(account_id: str):
    message = f"account_info\n{account_id}"
    return bank_custom(message)

def bank_status():
    return bank_custom("status")

def bank_time():
    return bank_custom("time")
