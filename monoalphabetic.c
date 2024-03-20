#include <stdio.h>
#include <string.h>

// Define the substitution key (plaintext to ciphertext mapping)
const char substitution_key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";

// Function to encrypt a message using a monoalphabetic substitution cipher
void encrypt(char *plaintext, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = substitution_key[plaintext[i] - 'A'];
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[i] = '\0';
}

// Function to decrypt a message using a monoalphabetic substitution cipher
void decrypt(char *ciphertext, char *decrypted) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            int index = 0;
            while (substitution_key[index] != c) {
                index++;
            }
            decrypted[i] = 'A' + index;
        } else {
            decrypted[i] = c; // Keep non-alphabetic characters unchanged
        }
    }
    decrypted[i] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decrypted[100];

    printf("Enter a message (uppercase letters only): ");
    scanf("%s", plaintext);

    encrypt(plaintext, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    decrypt(ciphertext, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
