#include <stdio.h>
#include <math.h>
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
int main() {
    int key_size = 25; 
    long double possible_keys = (long double)factorial(key_size);
    possible_keys /= key_size; 
    double log_base_2 = log2(possible_keys);
    printf("Approximate number of possible Playfair keys: 2^%.2lf\n", log_base_2);
    return 0;
}
