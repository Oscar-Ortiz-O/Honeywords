#include <stdio.h>
#include <winsock2.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int client_address_len = sizeof(client_address);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    // Initialize server address struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Socket bind failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a connection from a client
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) == INVALID_SOCKET) {
            printf("Accept failed.\n");
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        // Read and process data from the client
        char buffer[MAX_BUFFER_SIZE];
        int bytes_received;

        while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            printf("Received: %s", buffer);

            // Check if the message starts with "login"
            if (strncmp(buffer, "login", 5) == 0) {
                // Respond with "true"
                const char* response = "true";
                send(client_socket, response, strlen(response), 0);
            // Check if the message starts with "login"
            } else if (strncmp(buffer, "register", 8) == 0) {
                // Echo back to the client
                const char* response = "false";
                send(client_socket, response, strlen(response), 0);
            }
        }

        if (bytes_received == 0) {
            // Connection closed by the client
            printf("Client disconnected.\n");
        } else if (bytes_received == SOCKET_ERROR) {
            // Error in receiving data
            printf("Receive failed.\n");
        }

        // Close the client socket
        closesocket(client_socket);
    }

    // The server will never reach this point unless there's an error in the loop
    // Close the server socket
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
