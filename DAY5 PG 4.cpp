#include <stdio.h>

// Constants for block sizes
#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128

// Constants for left shift and XOR
#define SHIFT_CONST_64 0x1B
#define SHIFT_CONST_128 0x87

void generateSubkeys(unsigned char *originalKey, unsigned char *subKey1, unsigned char *subKey2, int block_size) {
    // Initialize subKey1 with the originalKey
    for (int i = 0; i < block_size / 8; i++) {
        subKey1[i] = originalKey[i];
        subKey2[i] = 0;  // Initialize subKey2 with zeros
    }

    // Check if the leftmost bit of subKey1 overflows
    if (subKey1[0] & 0x80) {
        // Perform left shift
        for (int i = 0; i < block_size / 8 - 1; i++) {
            subKey1[i] = (subKey1[i] << 1) | ((subKey1[i + 1] & 0x80) >> 7);
        }
        subKey1[block_size / 8 - 1] = (subKey1[block_size / 8 - 1] << 1);

        // XOR with the appropriate constant
        if (block_size == BLOCK_SIZE_64) {
            subKey1[block_size / 8 - 1] ^= SHIFT_CONST_64;
        } else if (block_size == BLOCK_SIZE_128) {
            subKey1[block_size / 8 - 1] ^= SHIFT_CONST_128;
        }
    } else {
        // Perform left shift without XOR
        for (int i = 0; i < block_size / 8 - 1; i++) {
            subKey1[i] = (subKey1[i] << 1) | ((subKey1[i + 1] & 0x80) >> 7);
        }
        subKey1[block_size / 8 - 1] = (subKey1[block_size / 8 - 1] << 1);
    }

    // Generate subKey2 in the same way as subKey1
    for (int i = 0; i < block_size / 8; i++) {
        subKey2[i] = subKey1[i];
    }
}

int main() {
    unsigned char originalKey_64[8] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6};
    unsigned char subKey1_64[8];
    unsigned char subKey2_64[8];

    unsigned char originalKey_128[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x12, 0x34, 0xCD, 0xE3, 0xBE, 0x12};
    unsigned char subKey1_128[16];
    unsigned char subKey2_128[16];

    generateSubkeys(originalKey_64, subKey1_64, subKey2_64, BLOCK_SIZE_64);
    generateSubkeys(originalKey_128, subKey1_128, subKey2_128, BLOCK_SIZE_128);

    printf("SubKey1 for block size 64: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subKey1_64[i]);
    }
    printf("\n");

    printf("SubKey2 for block size 64: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subKey2_64[i]);
    }
    printf("\n");

    printf("SubKey1 for block size 128: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", subKey1_128[i]);
    }
    printf("\n");

    printf("SubKey2 for block size 128: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", subKey2_128[i]);
    }
    printf("\n");

    return 0;
}
