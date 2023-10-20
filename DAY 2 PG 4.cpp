def initialize_matrix(key):
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"  # The letter 'J' is usually omitted in Playfair
    key = key.upper()
    matrix = []
    for char in key:
        if char not in matrix and char in alphabet:
            matrix.append(char)
    for char in alphabet:
        if char not in matrix:
            matrix.append(char)
    matrix = [matrix[i:i + 5] for i in range(0, 25, 5)]
    return matrix

def decode_playfair(ciphertext, key):
    matrix = initialize_matrix(key)
    ciphertext = ciphertext.replace(" ", "").upper()
    plaintext = ""
    i = 0
    while i < len(ciphertext):
        if i == len(ciphertext) - 1:
            pair = ciphertext[i] + "X"
            i += 2
        elif ciphertext[i] == ciphertext[i + 1]:
            pair = ciphertext[i] + "X"
            i += 1
        else:
            pair = ciphertext[i] + ciphertext[i + 1]
            i += 2
        row1, col1 = 0, 0
        row2, col2 = 0, 0
        for row in range(5):n
            for col in range(5):
                if matrix[row][col] == pair[0]:
                    row1, col1 = row, col
                if matrix[row][col] == pair[1]:
                    row2, col2 = row, col
        if row1 == row2:
            plaintext += matrix[row1][(col1 - 1) % 5] + matrix[row2][(col2 - 1) % 5]
        elif col1 == col2:
            plaintext += matrix[(row1 - 1) % 5][col1] + matrix[(row2 - 1) % 5][col2]
        else:
            plaintext += matrix[row1][col2] + matrix[row2][col1]
    return plaintext

ciphertext = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ"
key = "KEYWORD"  # Replace with your Playfair key
decoded_message = decode_playfair(ciphertext, key)
print(decoded_message)
