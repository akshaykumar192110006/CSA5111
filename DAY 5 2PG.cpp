#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt(const unsigned char *input, const unsigned char *key, unsigned char *output) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    // Set the DES key from the provided 56-bit key
    memcpy(des_key, key, 8);

    DES_set_odd_parity(&des_key);
    if (DES_set_key_checked(&des_key, &key_schedule) != 0) {
        fprintf(stderr, "Error setting DES key schedule\n");
        exit(1);
    }

    // Encrypt the input
    DES_ecb_encrypt((DES_cblock *)input, (DES_cblock *)output, &key_schedule, DES_ENCRYPT);
}

void des_decrypt(const unsigned char *input, const unsigned char *key, unsigned char *output) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    // Set the DES key from the provided 56-bit key
    memcpy(des_key, key, 8);

    DES_set_odd_parity(&des_key);
    if (DES_set_key_checked(&des_key, &key_schedule) != 0) {
        fprintf(stderr, "Error setting DES key schedule\n");
        exit(1);
    }

    // Decrypt the input
    DES_ecb_encrypt((DES_cblock *)input, (DES_cblock *)output, &key_schedule, DES_DECRYPT);
}

int main() {
    const unsigned char plaintext[8] = "12345678"; // 64-bit input
    unsigned char key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1}; // 56-bit key

    unsigned char ciphertext[8];
    unsigned char decryptedtext[8];

    // Encrypt the plaintext
    des_encrypt(plaintext, key, ciphertext);

    // Decrypt the ciphertext
    des_decrypt(ciphertext, key, decryptedtext);

    printf("Original: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted: %s\n", decryptedtext);

    return 0;
}
