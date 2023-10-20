#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

// AES block size
#define AES_BLOCK_SIZE 16

void encryptECB(const unsigned char* plaintext, const unsigned char* key, unsigned char* ciphertext, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &aesKey);
    }
}

void decryptECB(const unsigned char* ciphertext, const unsigned char* key, unsigned char* plaintext, size_t length) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, plaintext + i, &aesKey);
    }
}

void encryptCBC(const unsigned char* plaintext, const unsigned char* key, const unsigned char* iv, unsigned char* ciphertext, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    unsigned char xorBlock[AES_BLOCK_SIZE];
    memcpy(xorBlock, iv, AES_BLOCK_SIZE);
    
    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[i + j] ^= xorBlock[j];
        }
        AES_encrypt(plaintext + i, ciphertext + i, &aesKey);
        memcpy(xorBlock, ciphertext + i, AES_BLOCK_SIZE);
    }
}

void decryptCBC(const unsigned char* ciphertext, const unsigned char* key, const unsigned char* iv, unsigned char* plaintext, size_t length) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    unsigned char xorBlock[AES_BLOCK_SIZE];
    
    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, plaintext + i, &aesKey);
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[i + j] ^= iv[j];
        }
        memcpy(iv, ciphertext + i, AES_BLOCK_SIZE);
    }
}

void encryptCFB(const unsigned char* plaintext, const unsigned char* key, const unsigned char* iv, unsigned char* ciphertext, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    unsigned char feedback[AES_BLOCK_SIZE];
    memcpy(feedback, iv, AES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_encrypt(feedback, feedback, &aesKey);
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ feedback[j];
        }
    }
}

void decryptCFB(const unsigned char* ciphertext, const unsigned char* key, const unsigned char* iv, unsigned char* plaintext, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    unsigned char feedback[AES_BLOCK_SIZE];
    memcpy(feedback, iv, AES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_encrypt(feedback, feedback, &aesKey);
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ feedback[j];
        }
    }
}

int main() {
    unsigned char key[16] = "mysecretkey12345";
    unsigned char iv[16] = "initialvector123";
    unsigned char plaintext[] = "This is a message!";
    size_t textLength = strlen((char*)plaintext);

    unsigned char ciphertext[textLength];
    unsigned char decryptedText[textLength];

    // Encrypt using ECB mode
    encryptECB(plaintext, key, ciphertext, textLength);

    // Decrypt using ECB mode
    decryptECB(ciphertext, key, decryptedText, textLength);

    printf("ECB Decrypted Text: %s\n", decryptedText);

    // Encrypt using CBC mode
    encryptCBC(plaintext, key, iv, ciphertext, textLength);

    // Decrypt using CBC mode
    decryptCBC(ciphertext, key, iv, decryptedText, textLength);

    printf("CBC Decrypted Text: %s\n", decryptedText);

    // Encrypt using CFB mode
    encryptCFB(plaintext, key, iv, ciphertext, textLength);

    // Decrypt using CFB mode
    decryptCFB(ciphertext, key, iv, decryptedText, textLength);

    printf("CFB Decrypted Text: %s\n", decryptedText);

    return 0;
}
