#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to generate a random prime number
int generatePrime() {
    // Code to generate a random prime number (not shown)
    // Replace with a suitable method to generate prime numbers
    return 0;
}

int main() {
    int p, q, n, phi, e, d, plaintext, ciphertext, decryptedtext;

    // Generate two random prime numbers p and q
    p = generatePrime();
    q = generatePrime();

    // Calculate n and phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose a public exponent e (usually a small prime number)
    e = 17; // Example value, you can choose a different e

    // Calculate the private exponent d
    d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }

    // Encryption
    printf("Enter a plaintext: ");
    scanf("%d", &plaintext);
    ciphertext = fmod(pow(plaintext, e), n);
    printf("Ciphertext: %d\n", ciphertext);

    // Decryption
    decryptedtext = fmod(pow(ciphertext, d), n);
    printf("Decrypted Text: %d\n", decryptedtext);

    return 0;
}
