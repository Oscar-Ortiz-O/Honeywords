import socket

HOST = 'localhost'
PORT = 8080

def client_socket(message):
    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            # Connect the socket to the port where the server is listening
            server_address = (HOST, PORT)
            print("Connecting to {} port: {}".format(*server_address))
            sock.connect(server_address)

            # Take in data to send to the server
            message_to_send = message

            # Send data
            message_bytes = message_to_send.encode('utf-8')
            print("Sending {!r}".format(message_bytes))
            sock.sendall(message_bytes)

            # Receive and print the response from the server
            response = sock.recv(1024)
            decoded_response = response.decode('utf-8')
            print("Received response from server: {!r}".format(response.decode('utf-8')))
            return decoded_response

        except OSError as e:
            print("Error with client socket")
            print(e)
        finally:
            print("Closing socket")
