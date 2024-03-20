#include <stdio.h>
#include <string.h>

// Function to decrypt the ciphertext
void decrypt(char ciphertext[]) {
    // Define the substitution mapping
    char mapping[256];
    strcpy(mapping, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789][)(}{><");

    // Define the ciphertext and plaintext strings
    char plaintext[1000];
    int i;

    // Decrypt each character in the ciphertext
    for (i = 0; i < strlen(ciphertext); i++) {
        // Check if the character is in the mapping
        if (ciphertext[i] >= ' ' && ciphertext[i] <= '~') {
            // Find the corresponding character in the mapping and append it to the plaintext
            plaintext[i] = mapping[ciphertext[i] - ' '];
        } else {
            // If the character is not in the mapping, keep it unchanged
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0'; // Add null terminator to the plaintext string

    // Print the decrypted plaintext
    printf("Decrypted plaintext: %s\n", plaintext);
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    decrypt(ciphertext);

    return 0;
}

