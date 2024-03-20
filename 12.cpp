#include <stdio.h>

#define SIZE 2

// Function to encrypt the plaintext using the Hill cipher
void encryptHillCipher(int plaintext[], int key[][SIZE], int n) {
    int ciphertext[n];

    // Perform matrix multiplication
    for (int i = 0; i < n; i += SIZE) {
        ciphertext[i] = (key[0][0] * plaintext[i] + key[0][1] * plaintext[i + 1]) % 26;
        ciphertext[i + 1] = (key[1][0] * plaintext[i] + key[1][1] * plaintext[i + 1]) % 26;
    }

    // Print the ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < n; i++) {
        printf("%c", ciphertext[i] + 'a');
    }
    printf("\n");
}

// Function to decrypt the ciphertext using the Hill cipher
void decryptHillCipher(int ciphertext[], int key[][SIZE], int n) {
    int plaintext[n];

    // Calculate the inverse of the key matrix
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    int invDet = 0;
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            invDet = i;
            break;
        }
    }
    int invKey[SIZE][SIZE] = {
        {key[1][1], -key[0][1]},
        {-key[1][0], key[0][0]}
    };
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            invKey[i][j] = (invKey[i][j] * invDet) % 26;
            if (invKey[i][j] < 0) {
                invKey[i][j] += 26;
            }
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < n; i += SIZE) {
        plaintext[i] = (invKey[0][0] * ciphertext[i] + invKey[0][1] * ciphertext[i + 1]) % 26;
        plaintext[i + 1] = (invKey[1][0] * ciphertext[i] + invKey[1][1] * ciphertext[i + 1]) % 26;
    }

    // Print the decrypted plaintext
    printf("Decrypted plaintext: ");
    for (int i = 0; i < n; i++) {
        printf("%c", plaintext[i] + 'a');
    }
    printf("\n");
}

int main() {
    // Given plaintext
    int plaintext[] = {12, 4, 4, 19, 12, 4, 19, 19, 19, 1, 20, 8, 5, 21, 19, 1, 12, 19, 4, 18, 1, 20, 8, 19, 1, 14, 7, 8, 19, 0, 3, 11, 14, 2, 17, 7, 13, 4, 18, 19, 7, 8, 20, 14, 18, 14, 10};
    // Given key matrix
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    // Number of characters in the plaintext
    int n = sizeof(plaintext) / sizeof(plaintext[0]);

    // Encrypt the plaintext using the Hill cipher
    printf("Plaintext: meet me at the usual place at ten rather than eight oclock\n");
    encryptHillCipher(plaintext, key, n);

    // Given ciphertext
    int ciphertext[] = {10, 0, 1, 19, 4, 0, 19, 19, 19, 0, 19, 8, 0, 2, 19, 19, 10, 19, 4, 0, 17, 19, 0, 2, 19, 19, 14, 5, 8, 19, 24, 18, 10, 14, 2, 17, 14, 2, 11, 14, 19, 0, 17, 4, 19, 17, 14};
    // Decrypt the ciphertext using the Hill cipher
    decryptHillCipher(ciphertext, key, n);

    return 0;
}
