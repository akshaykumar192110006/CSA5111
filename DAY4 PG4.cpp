from Crypto.PublicKey import RSA

# Receiver's public key (n, e)
n = 1234567890  # Replace with the actual modulus
e = 65537  # Replace with the actual public exponent

# Plaintext block to be encrypted
plaintext_block = 42  # Replace with your actual plaintext block

# Encrypt using RSA
public_key = RSA.construct((n, e))
cipher_text = public_key.encrypt(plaintext_block, 0)[0]

print("Encrypted Block:", cipher_text)
