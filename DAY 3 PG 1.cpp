def vigenere_encrypt(plaintext, key_stream):
    ciphertext = ""
    for i in range(len(plaintext)):
        if plaintext[i].isalpha():
            shift = key_stream[i % len(key_stream)]
            if plaintext[i].islower():
                offset = ord('a')
            else:
                offset = ord('A')
            char_code = ord(plaintext[i]) - offset
            encrypted_char = chr((char_code + shift) % 26 + offset)
            ciphertext += encrypted_char
        else:
            ciphertext += plaintext[i]
    return ciphertext

# Part a
plaintext_a = "sendmoremoney"
key_stream_a = [9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9]
ciphertext_a = vigenere_encrypt(plaintext_a, key_stream_a)
print("Ciphertext (Part a):", ciphertext_a)
