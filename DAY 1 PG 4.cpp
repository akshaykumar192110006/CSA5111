#include <stdio.h>
#include <string.h>

void caesarCipher(char *text, int shift) {
    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            text[i] = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            text[i] = 'A' + (c - 'A' + shift) % 26;
        }
    }
}

int main() {
    char text[100];
    int shift;

    printf("Enter text: ");
    gets(text); // Warning: gets() is not safe, but for simplicity in this example

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    if (shift >= 1 && shift <= 25) {
        caesarCipher(text, shift);
        printf("Caesar Cipher: %s\n", text);
    } else {
        printf("Shift value must be between 1 and 25.\n");
    }

    return 0;
}
