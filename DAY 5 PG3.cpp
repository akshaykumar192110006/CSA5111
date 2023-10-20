#include <stdio.h>
#include <string.h>

// AES Encryption Function (Assuming you have an AES encryption function)
// Replace this with your actual AES encryption function
void AES_Encrypt(unsigned char* data, unsigned char* key) {
    // Replace this with AES encryption logic
    // ...
}

// XOR operation for two blocks
void XOR(unsigned char* block1, unsigned char* block2) {
    for (int i = 0; i < 16; i++) {
        block1[i] ^= block2[i];
    }
}

// CBC-MAC Function
void CBC_MAC(unsigned char* key, unsigned char* message, unsigned char* mac) {
    unsigned char iv[16] = {0}; // Initialization Vector

    // Encrypt the message block with the key using CBC mode
    AES_Encrypt(iv, key);
    XOR(iv, message);

    // Copy the result to the MAC
    memcpy(mac, iv, 16);
}

int main() {
    unsigned char key[16] = "YourSecretKey"; // 16-byte secret key
    unsigned char message[16] = "YourMessageX"; // 16-byte message
    unsigned char mac[16];

    CBC_MAC(key, message, mac);

    printf("MAC for X: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    // Create X || (X ? T)
    unsigned char x_xor_t[16];
    memcpy(x_xor_t, message, 16); // Copy X to x_xor_t
    CBC_MAC(key, x_xor_t, mac);

    printf("MAC for X || (X ? T): ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}
