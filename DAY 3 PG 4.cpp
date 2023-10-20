def generate_subkeys(initial_key):
    # Perform the initial key permutation (PC-1)
    key = initial_permutation(initial_key)
    
    # Split the 56-bit key into two 28-bit halves
    left_half, right_half = split_key(key)

    subkeys = []
    for round_number in range(16):
        # Apply the circular left shift to both halves
        left_half = circular_left_shift(left_half, shift_amount[round_number])
        right_half = circular_left_shift(right_half, shift_amount[round_number])

        # Combine the two 28-bit halves
        combined_key = combine_halves(left_half, right_half)

        # Perform the round key permutation (PC-2) to obtain a 48-bit subkey
        subkey = round_key_permutation(combined_key)

        subkeys.append(subkey)

    return subkeys
