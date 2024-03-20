#include <stdio.h>
#include <string.h>
// Function to perform Caesar cipher encryption
void encryptCaesarCipher(char text[], int shift) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] + shift - 'A') % 26 + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] + shift - 'a') % 26 + 'a';
        }
    }
}
int main() {
    char text[100];
    int shift;
    printf("Enter text to be encrypted: ");
    scanf("%[^\n]s", text);
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    encryptCaesarCipher(text, shift);
    printf("Encrypted text: %s\n", text);
    return 0;
}
