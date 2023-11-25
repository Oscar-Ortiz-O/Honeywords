#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
