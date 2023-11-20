import socket

HOST = 'localhost'
PORT = 10000


def server_socket():
    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:

        # Bind the socket to the port
        server_address = (HOST, PORT)
        print("Starting up on {} port {}".format(*server_address))
        sock.bind(server_address)

        # Listen for incoming connections
        sock.listen(1)

        while True:
            # Wait for a connection
            print("Waiting for a connection")
            connection, client_address = sock.accept()
            try:
                print("Connection from", client_address)
                # Receive the data in small chunks and retransmit it
                while True:
                    data = connection.recv(1024)
                    print("Received {!r}".format(data))
                    if data:
                        print("Sending data back to the client")
                        connection.sendall(data)
                    else:
                        print("No data from", client_address)
                        break
            except OSError as e:
                print("Error reading client data")
                print(e)
            finally:
                # Clean up the connection
                connection.close()


if __name__ == '__main__':
    server_socket()