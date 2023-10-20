from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend

# Initialize a 3DES key and IV (Initialization Vector)
key = b'secretkey12345678'
iv = b'initialvec1234567'

# Create a 3DES cipher object
cipher = Cipher(algorithms.TripleDES(key), modes.CBC(iv), backend=default_backend())

# Create an encryptor
encryptor = cipher.encryptor()

# Message to be encrypted
message = b'Secret message to be encrypted'

# PKCS7 padding
padder = padding.PKCS7(64).padder()
padded_data = padder.update(message) + padder.finalize()

# Encrypt the message
ciphertext = encryptor.update(padded_data) + encryptor.finalize()

print("Ciphertext:", ciphertext.hex())
