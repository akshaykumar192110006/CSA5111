#include <stdio.h>
#include <openssl>
#include <openssl/bn.h>

int main() 
{
    // DSA key generation
    DSA* dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(dsa);

    // Message to be signed
    unsigned char message[] = "Hello, world!";
    int message_len = strlen((char*)message);

    // Signature generation
    unsigned char signature[DSA_size(dsa)];
    unsigned int signature_len;
    DSA_sign(0, message, message_len, signature, &signature_len, dsa);

    // Verify the signature
    int verification_result = DSA_verify(0, message, message_len, signature, signature_len, dsa);

    if (verification_result == 1) {
        printf("DSA Signature verified successfully.\n");
    } else {
        printf("DSA Signature verification failed.\n");
    }

    // Clean up
    DSA_free(dsa);

    return 0;
}
