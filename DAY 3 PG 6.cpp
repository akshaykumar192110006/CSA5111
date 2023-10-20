#include <stdio.h>
#include <string.h>

// Define the key (128 bits)
unsigned char key[] = "0123456789ABCDEF";

// Define the data to be encrypted (multiple blocks)
unsigned char data[2][16] = {
    "Hello, World!!!",
    "This is ECB mode."
};

// AES S-Box (used for encryption)
unsigned char sBox[256] = {
   // S-Box values
};

// SubBytes transformation
void SubBytes(unsigned char* state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sBox[state[i]];
    }
}

// AddRoundKey transformation (XOR with the round key)
void AddRoundKey(unsigned char* state, unsigned char* roundKey) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKey[i];
    }
}

// AES encryption for a single block
void EncryptBlock(unsigned char* input, unsigned char* output, unsigned char* roundKey) {
    unsigned char state[16];
    
    // Copy input to state
    for (int i = 0; i < 16; i++) {
        state[i] = input[i];
    }

    // Initial round
    AddRoundKey(state, roundKey);

    // Main rounds
    for (int round = 1; round < 10; round++) {
        SubBytes(state);
        AddRoundKey(state, roundKey + round * 16);
    }

    // Final round
    SubBytes(state);
    AddRoundKey(state, roundKey + 10 * 16);

    // Copy state to output
    for (int i = 0; i < 16; i++) {
        output[i] = state[i];
    }
}

int main() {
    unsigned char roundKeys[176]; // AES round keys (expanded from the original key)
    unsigned char encryptedData[2][16]; // Store encrypted data

    // Key expansion (not shown in this example)

    // Encrypt each block of data
    for (int block = 0; block < 2; block++) {
        EncryptBlock(data[block], encryptedData[block], roundKeys);
    }

    // Print the encrypted data
    for (int block = 0; block < 2; block++) {
        printf("Block %d: ", block + 1);
        for (int i = 0; i < 16; i++)
