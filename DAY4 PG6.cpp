#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    // Generate or load Bob's public and private keys (usually, this should be done securely)
    RSA *rsa = RSA_generate_key(2048, 65537, NULL, NULL);

    // Message to be encrypted
    const char* message = "HELLO";

    // Buffer to store the encrypted message
    unsigned char encrypted[256]; // Adjust the size according to your key length

    // Encrypt the message
    int encrypted_length = RSA_public_encrypt(strlen(message), (const unsigned char*)message, encrypted, rsa, RSA_PKCS1_PADDING);
    if (encrypted_length == -1) {
        fprintf(stderr, "Encryption failed\n");
        return 1;
    }

    // Decrypt the message (this is for demonstration purposes)
    unsigned char decrypted[256]; // Adjust the size according to your key length
    int decrypted_length = RSA_private_decrypt(encrypted_length, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (decrypted_length == -1) {
        fprintf(stderr, "Decryption failed\n");
        return 1;
    }

    decrypted[decrypted_length] = '\0'; // Null-terminate the decrypted message

    printf("Original message: %s\n", message);
    printf("Encrypted message: %s\n", encrypted);
    printf("Decrypted message: %s\n", decrypted);

    RSA_free(rsa); // Free RSA key resources

    return 0;
}
