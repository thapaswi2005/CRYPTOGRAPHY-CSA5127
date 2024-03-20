#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define GRID_SIZE 5
#define MAX_SIZE 100

// Function to prepare the key by removing duplicate letters and appending the rest of the alphabet
void prepareKey(char *key, char *preparedKey) {
    int keyLen = strlen(key);
    int preparedIndex = 0;
    int i, j;

    // Copy the key into preparedKey
    strcpy(preparedKey, key);

    // Remove duplicate letters from the key
    for (i = 0; i < keyLen; i++) {
        if (preparedKey[i] == 'J') {
            preparedKey[i] = 'I'; // Replace 'J' with 'I'
        }
        for (j = i + 1; j < keyLen; j++) {
            if (preparedKey[i] == preparedKey[j]) {
                memmove(&preparedKey[j], &preparedKey[j + 1], keyLen - j);
                keyLen--;
            }
        }
    }

    // Append the rest of the alphabet (except 'J')
    for (i = 0; i < 26; i++) {
        if ('A' + i != 'J' && !strchr(preparedKey, 'A' + i)) {
            preparedKey[keyLen++] = 'A' + i;
        }
    }
    preparedKey[keyLen] = '\0';
}

// Function to find the positions of two characters in the Playfair grid
void findPositions(char grid[GRID_SIZE][GRID_SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char *message, char *key) {
    char grid[GRID_SIZE][GRID_SIZE];
    char preparedKey[GRID_SIZE * GRID_SIZE];
    int i, j, k;

    // Prepare the key
    prepareKey(key, preparedKey);

    // Populate the Playfair grid
    k = 0;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = preparedKey[k++];
        }
    }

    // Encrypt the message
    for (i = 0; message[i] != '\0'; i += 2) {
        int row1, col1, row2, col2;
        char ch1 = message[i];
        char ch2 = (message[i + 1] == '\0') ? 'X' : message[i + 1]; // Pad with 'X' if the message length is odd

        // Find positions of characters in the grid
        findPositions(grid, ch1, &row1, &col1);
        findPositions(grid, ch2, &row2, &col2);

        // Same row
        if (row1 == row2) {
            printf("%c%c", grid[row1][(col1 + 1) % GRID_SIZE], grid[row2][(col2 + 1) % GRID_SIZE]);
        }
        // Same column
        else if (col1 == col2) {
            printf("%c%c", grid[(row1 + 1) % GRID_SIZE][col1], grid[(row2 + 1) % GRID_SIZE][col2]);
        }
        // Different row and column
        else {
            printf("%c%c", grid[row1][col2], grid[row2][col1]);
        }
    }
}

int main() {
    char message[MAX_SIZE] = "Must see you over Cadogan West. Coming at once";
    char key[] = "MFHIJ KUNOPQZVWXYELARGS TBC"; // Playfair key

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    encryptPlayfair(message, key);
    printf("\n");

    return 0;
}
