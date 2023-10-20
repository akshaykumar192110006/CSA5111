# Initial permutation IP
def initial_permutation(block):
    # Apply the initial permutation (IP) to the 64-bit block
    return permute(block, IP)

# Final permutation IP^-1
def final_permutation(block):
    # Apply the final permutation (IP^-1) to the 64-bit block
    return permute(block, IP_inverse)

# Key generation for decryption (use keys in reverse order)
def generate_keys_reverse_order(master_key):
    keys = generate_keys(master_key)
    return keys[::-1]

# Decryption function
def decrypt(ciphertext, master_key):
    # Generate subkeys in reverse order
    subkeys = generate_keys_reverse_order(master_key)
    
    # Initial permutation
    ciphertext = initial_permutation(ciphertext)
    
    # Perform 16 rounds of Feistel network
    for round_num in range(16):
        # Split the 64-bit block into left and right halves
        left, right = split_block(ciphertext)
        
        # Perform the Feistel function
        new_right = feistel_function(right, subkeys[round_num])
        
        # XOR the result of the Feistel function with the left half
        new_left = left ^ new_right
        
        # Swap left and right for the next round
        left = right
        right = new_left
        
        # Combine left and right
        ciphertext = combine_blocks(left, right)
    
    # Perform the final permutation
    plaintext = final_permutation(ciphertext)
    
    return plaintext
