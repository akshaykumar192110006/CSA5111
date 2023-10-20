#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the multiplicative inverse of e modulo f(n)
int modInverse(int e, int fn) {
    for (int d = 2; d < fn; d++) {
        if ((e * d) % fn == 1) {
            return d;
        }
    }
    return -1; // No multiplicative inverse found
}

int main() {
    int e = 31;
    int n = 3599;

    // Find p and q through trial and error
    int p, q;
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    if (p >= n || q >= n) {
        printf("Could not determine p and q.\n");
        return 1;
    }

    int fn = (p - 1) * (q - 1);

    // Calculate the private key (d) using the extended Euclidean algorithm
    int d = modInverse(e, fn);

    if (d == -1) {
        printf("Private key not found.\n");
        return 1;
    }

    printf("p = %d, q = %d\n", p, q);
    printf("Private key (d) = %d\n", d);

    return 0;
}
