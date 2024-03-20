#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to remove spaces and non-alphabetic characters from a string
void cleanString(char *plaintext) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[j++] = toupper(plaintext[i]);
        }
    }
    plaintext[j] = '\0';
}

// Function to generate the Playfair matrix from the key
void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    int i, j, k = 0;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: 'J' is skipped
    int len = strlen(key);

    // Fill the key in the matrix
    for (i = 0; i < len; i++) {
        if (key[i] != 'J') {
            matrix[k / SIZE][k % SIZE] = key[i];
            alphabet[key[i] - 'A'] = 0; // Mark the letter as used
            k++;
        }
    }

    // Fill the remaining alphabet in the matrix
    for (i = 0; i < 26; i++) {
        if (alphabet[i] != 0) {
            matrix[k / SIZE][k % SIZE] = alphabet[i];
            k++;
        }
    }
}

// Function to find the coordinates of a character in the matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt the Playfair cipher
void decryptPlayfairCipher(char ciphertext[], char key[]) {
    char matrix[SIZE][SIZE];
    char plaintext[strlen(ciphertext)]; // Assuming plaintext won't be longer than ciphertext
    int i, j, row1, col1, row2, col2;

    // Remove spaces and non-alphabetic characters from the ciphertext
    cleanString(ciphertext);

    // Generate the Playfair matrix from the key
    generateMatrix(key, matrix);

    // Decrypt the ciphertext
    for (i = 0; i < strlen(ciphertext); i += 2) {
        findPosition(matrix, ciphertext[i], &row1, &col1);
        findPosition(matrix, ciphertext[i + 1], &row2, &col2);

        // If the letters are in the same row, replace them with the letters to their immediate right
        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        }
        // If the letters are in the same column, replace them with the letters immediately below
        else if (col1 == col2) {
            plaintext[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        }
        // Otherwise, form a rectangle and replace them with the letters on the same row but at the other pair of corners
        else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }

    plaintext[strlen(ciphertext)] = '\0';
    printf("Decrypted message: %s\n", plaintext);
}

int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char key[] = "KEYWORD";

    printf("Ciphertext: %s\n", ciphertext);
    decryptPlayfairCipher(ciphertext, key);

    return 0;
}
