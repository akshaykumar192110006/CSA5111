#include <stdio.h>
#include <math.h>

// Function to calculate (base^exponent) % mod
int mod_pow(int base, int exponent, int mod) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

int main() {
    int q = 23; // Public prime number
    int a = 5;  // Public base
    int xAlice = 6; // Alice's secret number
    int xBob = 15;  // Bob's secret number

    // Alice computes A = (a^xAlice) % q
    int A = mod_pow(a, xAlice, q);

    // Bob computes B = (a^xBob) % q
    int B = mod_pow(a, xBob, q);

    // Alice and Bob exchange A and B

    // Alice computes the shared key
    int sharedKeyAlice = mod_pow(B, xAlice, q);

    // Bob computes the shared key
    int sharedKeyBob = mod_pow(A, xBob, q);

    // Both Alice and Bob now have the same sharedKey
    printf("Shared key at Alice: %d\n", sharedKeyAlice);
    printf("Shared key at Bob: %d\n", sharedKeyBob);

    return 0;
}
