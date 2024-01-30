#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Test
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
    char inputedUser[50];
    char inputedPass[50];

    printf("Enter username: ");
    fgets(inputedUser, sizeof(inputedUser), stdin);
    inputedUser[strcspn(inputedUser, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputedPass, sizeof(inputedPass), stdin);
    inputedPass[strcspn(inputedPass, "\n")] = '\0'; // Remove newline character

    const char *passFileName = "passwordFile.txt";

    int result = findPassword(inputedUser, inputedPass, passFileName);

    if (result != -1) {
        printf("Password found at index: %d\n", result);
    } else {
        printf("Username and/or password not found.\n");
    }

    return 0;
}
