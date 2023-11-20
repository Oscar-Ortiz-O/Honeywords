import socket

HOST = 'localhost'
PORT = 10000


def client_socket(message):
    # Create a TCP/IP socket
    # with automatically will call sock.close()
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            # Connect the socket to the port where the server is listening
            server_address = (HOST, PORT)
            print("Connecting to {} port: {}".format(*server_address))
            sock.connect(server_address)

            # Send data
            print("Sending {!r}".format(message))
            sock.sendall(message)

            # Look for the response
            amount_received = 0
            amount_expected = len(message)

            while amount_received < amount_expected:
                data = sock.recv(1024)
                amount_received += len(data)
                print("Received {!r}".format(data))
        except OSError as e:
            print("Error with client socket")
            print(e)
        finally:
            print("Closing socket")


if __name__ == '__main__':
    # Send data
    message_to_send = b"This is the message"
    client_socket(message_to_send)