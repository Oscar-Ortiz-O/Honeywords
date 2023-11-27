#include <stdio.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

// Structure to hold both honeywords and the real password index
typedef struct {
    char **honeywords;
    int realPasswordIndex;
} HoneywordsResult;

// Function to generate a random number between min and max
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to generate honeywords
HoneywordsResult generateHoneywords(char *password, int numPositions, int numHoneywords) {
    HoneywordsResult result;

    int passwordLength = strlen(password);

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Allocate memory for honeywords
    result.honeywords = (char **)malloc((numHoneywords + 1) * sizeof(char *));  // +1 for the real password
    for (int i = 0; i <= numHoneywords; ++i) {
        result.honeywords[i] = (char *)malloc((passwordLength + 1) * sizeof(char));
    }

    // Copy the real password to a random position in the array
    result.realPasswordIndex = getRandomNumber(0, numHoneywords);
    strcpy(result.honeywords[result.realPasswordIndex], password);

    // Generate honeywords
    for (int i = 0; i < numHoneywords; ++i) {
        // Skip the position where the real password is already placed
        if (i == result.realPasswordIndex) {
            continue;
        }

        strcpy(result.honeywords[i], password);

        // Randomize positions starting from the end
        for (int j = 0; j < numPositions && j < passwordLength; ++j) {
            int randomPosition = passwordLength - 1 - j;

            // Ensure the replacement character is of the same type
            char originalChar = password[randomPosition];
            char randomChar;

            if (isdigit(originalChar)) {
                // Replace with a random digit
                randomChar = getRandomNumber('0', '9');
            } else if (islower(originalChar)) {
                // Replace with a random lowercase letter
                randomChar = getRandomNumber('a', 'z');
            } else if (isupper(originalChar)) {
                // Replace with a random uppercase letter
                randomChar = getRandomNumber('A', 'Z');
            } else {
                // Replace with a random character (e.g., special character)
                randomChar = getRandomNumber(33, 126);
            }

            result.honeywords[i][randomPosition] = randomChar;
        }
    }

    return result;
}

// Function to find a password in a file
int findPassword(const char *inputedUser, const char *inputedPass, const char *passFileName) {
    FILE *passFile = fopen(passFileName, "r");

    if (passFile == NULL) {
        perror("Error opening file");
        return -1; // Unable to open the file
    }

    char line[256]; // Assuming a maximum line length of 255 characters

    while (fgets(line, sizeof(line), passFile) != NULL) {
        char *token = strtok(line, ",");

        // Skip to next line if usernames do not match
        char *username = token;
        if (strcmp(username, inputedUser) != 0) {
            continue;
        }

        // Check if password is among the sweetwords.
        // If it is, get the index in which it was found.
        int index = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            if (strcmp(token, inputedPass) == 0) {
                fclose(passFile);
                return index;
            }
            index++;
        }
    }

    fclose(passFile);
    return -1; // If username and/or password was not found
}


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
        char username[MAX_BUFFER_SIZE];
        char password[MAX_BUFFER_SIZE];
        int bytes_received;

        while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            printf("Received: %s", buffer);

            char *token = strtok(buffer, "|");
            strcpy(username, strtok(NULL, "|"));
            strcpy(password, strtok(NULL, "|"));

            // Check if the message starts with "login"
            if (strcmp(token, "login") == 0) {

                // Respond with "true"
                const char* response = "true";
                send(client_socket, response, strlen(response), 0);

            // Check if the message starts with "register"
            } else if (strcmp(token, "register") == 0) {
                
                // Echo back to the client
                const char* response = "false";
                send(client_socket, response, strlen(response), 0);
            }
        }

        printf("Username: %s\n", username);
        printf("Password: %s\n", password);

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
