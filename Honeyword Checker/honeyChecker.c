#include <stdio.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "honeyChecker.h"


// Writes the username and password index ccombination to a passwordIndex.txt file
void writePasswordIndexToFile(const char *filename, const char *username, int realPasswordIndex) {
    FILE *file = fopen(filename, "a"); // Open file in append mode

    if (file != NULL) {
        // Write the username and real password index to the file
        fprintf(file, "%s,%d\n", username, realPasswordIndex);
        fclose(file); // Close the file
    } else {
        printf("Error opening file: %s\n", filename);
    }
}

// Function to check if the provided password index matches the stored one for a given username
int checkPasswordIndex(const char *filename, const char *username, int providedPasswordIndex) {
    FILE *file = fopen(filename, "r"); // Open file in read mode

    if (file != NULL) {
        char line[256];
        char storedUsername[256];
        int storedPasswordIndex;

        // Read lines from the file
        while (fgets(line, sizeof(line), file) != NULL) {
            // Parse the line to extract username and password index
            if (sscanf(line, "%[^,],%d", storedUsername, &storedPasswordIndex) == 2) {
                // Check if the current line corresponds to the provided username
                if (strcmp(storedUsername, username) == 0) {
                    fclose(file); // Close the file
                    // Return True if the provided password index matches the stored one
                    return (providedPasswordIndex == storedPasswordIndex);
                }
            }
        }

        fclose(file); // Close the file
    } else {
        printf("Error opening file: %s\n", filename);
    }

    // Return False if the username is not found or an error occurs
    return 0;
}

