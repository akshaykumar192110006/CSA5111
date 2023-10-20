import string

# Function to shift a letter by a given value
def shift_letter(letter, shift):
    if letter.isalpha():
        base = ord('A') if letter.isupper() else ord('a')
        return chr(((ord(letter) - base + shift) % 26) + base)
    else:
        return letter

# Function to decrypt a message with all possible shift values
def decrypt_caesar(ciphertext, shift):
    return ''.join(shift_letter(char, -shift) for char in ciphertext)

# Function to score plaintexts based on letter frequency
def score_plaintext(plaintext):
    letter_frequency = {
        'a': 8.167, 'b': 1.492, 'c': 2.782, 'd': 4.253, 'e': 12.702,
        'f': 2.228, 'g': 2.015, 'h': 6.094, 'i': 6.966, 'j': 0.153,
        'k': 0.772, 'l': 4.025, 'm': 2.406, 'n': 6.749, 'o': 7.507,
        'p': 1.929, 'q': 0.095, 'r': 5.987, 's': 6.327, 't': 9.056,
        'u': 2.758, 'v': 0.978, 'w': 2.360, 'x': 0.150, 'y': 1.974,
        'z': 0.074
    }
    score = sum(letter_frequency.get(char, 0) for char in plaintext.lower())
    return score

# Function to perform the frequency attack and return the top N plaintexts
def frequency_attack(ciphertext, top_n=10):
    possible_plaintexts = []
    for shift in range(26):
        decrypted_text = decrypt_caesar(ciphertext, shift)
        score = score_plaintext(decrypted_text)
        possible_plaintexts.append((decrypted_text, score))
    
    # Sort by score in descending order
    possible_plaintexts.sort(key=lambda x: x[1], reverse=True)

    return possible_plaintexts[:top_n]

# Example usage:
ciphertext = "Your ciphertext here"
top_plaintexts = frequency_attack(ciphertext, top_n=10)
for i, (text, score) in enumerate(top_plaintexts):
    print(f"Rank {i + 1}: Score = {score:.2f}\n{text}\n")
