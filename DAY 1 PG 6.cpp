#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int is_allowed_a(int a) {
    return gcd(a, 26) == 1; // 'a' is allowed if it's relatively prime to 26
}

int main() {
    int a, b;
    
    printf("Enter the value of 'a': ");
    scanf("%d", &a);
    
    if (!is_allowed_a(a)) {
        printf("Value of 'a' is not allowed. It must be relatively prime to 26.\n");
        return 1;
    }
    
    printf("Enter the value of 'b': ");
    scanf("%d", &b);
    
    if (b < 0 || b >= 26) {
        printf("Value of 'b' is not allowed. It must be in the range [0, 25].\n");
        return 1;
    }
    
    char plaintext;
    printf("Enter the plaintext character: ");
    scanf(" %c", &plaintext);
    
    if (plaintext >= 'A' && plaintext <= 'Z') {
        // Uppercase letter
        char ciphertext = 'A' + ((a * (plaintext - 'A') + b) % 26);
        printf("Ciphertext: %c\n", ciphertext);
    } else if (plaintext >= 'a' && plaintext <= 'z') {
        // Lowercase letter
        char ciphertext = 'a' + ((a * (plaintext - 'a') + b) % 26);
        printf("Ciphertext: %c\n", ciphertext);
    } else {
        printf("Invalid input. Please enter an uppercase or lowercase letter.\n");
        return 1;
    }
    
    return 0;
}
