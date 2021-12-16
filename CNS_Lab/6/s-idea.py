# Perform Left Shift operation
def leftshift(str, k):
    temp = list(str)
    for i in range(k):
        temp.append(temp.pop(0))
    return "".join(temp)


# Returning the multiplicative inverse of number a modulo m
def modInverse(a, m):
    for x in range(1, m):
        if ((a % m) * (x % m)) % m == 1:
            return x
    return -1


# checking for string having all zeros
def check_16(str1, str2):
    if int(str1, 2) == 0:
        str1 = "10000"
    if int(str2, 2) == 0:
        str2 = "10000"
    val = (int(str1, 2) * int(str2, 2)) % 17
    if val == 16:
        return 0
    return val


# Utility function to generate decryption keys
def do_arithmetic(key, previous_key):
    decryption_key = []

    decryption_key.append(bin(modInverse(int(key[0], 2), 17))[2:].zfill(4))
    decryption_key.append(bin(16 - int(key[1], 2))[2:].zfill(4))
    decryption_key.append(bin(16 - int(key[2], 2))[2:].zfill(4))
    decryption_key.append(bin(modInverse(int(key[3], 2), 17))[2:].zfill(4))
    decryption_key.append(previous_key[4])
    decryption_key.append(previous_key[5])
    return decryption_key


# Function which generates decryption keys
def generate_decryption_key(encryption_keys):
    decryption_keys = []
    for i, encryption_key in enumerate(encryption_keys):
        decryption_keys.insert(0, do_arithmetic(encryption_key, encryption_keys[i - 1]))
    return decryption_keys


# Function which generates encryption keys
def generate_encryption_keys(key):
    Key = []
    key1 = key
    encryption_keys = []
    for i in range(4):
        j = 0
        while len(Key) != 6:
            Key.append(key1[j : j + 4])
            j += 4
        encryption_keys.append(tuple(Key))
        key = key1
        key1 = leftshift(key, 6)
        Key.clear()
        count = int(((len(key) - j) / 4))
        while count:
            Key.append(key[j : j + 4])
            j += 4
            count -= 1
    encryption_keys.append(tuple(Key[:6]))
    return encryption_keys


# Main function which performs encryption/decryption
def encrypt(keys, plainText):
    x1 = plainText[0:4]
    x2 = plainText[4:8]
    x3 = plainText[8:12]
    x4 = plainText[12:16]
    for i in range(4):
        print("Keys   for round  ", i, end=" : ")
        for key in keys[i]:
            print(key, end=" ")
        print()
        # step 1 = X1 * K1
        val = check_16(x1, keys[i][0])
        step1 = bin(val)[2:].zfill(4)
        # step 2 = X2 + K2
        step2 = bin((int(x2, 2) + int(keys[i][1], 2)) % 16)[2:].zfill(4)
        # step 3 = X3 + K3
        step3 = bin((int(x3, 2) + int(keys[i][2], 2)) % 16)[2:].zfill(4)
        # step 4 = X4 * K4
        val = check_16(x4, keys[i][3])
        step4 = bin(val)[2:].zfill(4)
        # step 5 = Step 1 ^ Step 3
        step5 = bin(int(step1, 2) ^ int(step3, 2))[2:].zfill(4)
        # step 6 = Step 2 ^ Step 4
        step6 = bin(int(step2, 2) ^ int(step4, 2))[2:].zfill(4)
        # step 7 = Step 5 * K5
        val = check_16(step5, keys[i][4])
        step7 = bin(val)[2:].zfill(4)
        # step 8 = Step 6 + Step 7
        step8 = bin((int(step6, 2) + int(step7, 2)) % 16)[2:].zfill(4)
        # step 9 = Step 8 * K6
        val = check_16(step8, keys[i][5])
        step9 = bin(val)[2:].zfill(4)
        # step 10 = Step 7 + Step 9
        step10 = bin((int(step7, 2) + int(step9, 2)) % 16)[2:].zfill(4)
        # step 11 = Step 1 ^ Step 9
        x1 = bin(int(step1, 2) ^ int(step9, 2))[2:].zfill(4)
        # step 12 = Step 3 ^ Step 9
        x3 = bin(int(step3, 2) ^ int(step9, 2))[2:].zfill(4)
        # step 13 = Step 2 ^ Step 10
        x2 = bin(int(step2, 2) ^ int(step10, 2))[2:].zfill(4)
        # step 14 = Step 4 ^ Step 10
        x4 = bin(int(step4, 2) ^ int(step10, 2))[2:].zfill(4)
        print("Output of  round  ", i, ": ", x1, x2, x3, x4)
        print()
    print("Keys   for round ", 4.5, end=" : ")
    for key in keys[4]:
        print(key, end=" ")
    print()
    # step 1
    val = check_16(x1, keys[4][0])
    c1 = bin(val)[2:].zfill(4)
    # step 2
    c2 = bin((int(x2, 2) + int(keys[4][1], 2)) % 16)[2:].zfill(4)
    # step 3
    c3 = bin((int(x3, 2) + int(keys[4][2], 2)) % 16)[2:].zfill(4)
    # step 4
    val = check_16(x4, keys[4][3])
    c4 = bin(val)[2:].zfill(4)

    print("Output of  round  ", 4.5, " : ", c1, c2, c3, c4)
    return c1 + c2 + c3 + c4


key = input("Enter 32 bit key in binary\n")
plainText = input("Enter 16 bit plaintext in binary\n")

# generating keys for encryption
encryption_keys = generate_encryption_keys(key)

# Encrypting plaintext
cipherText = encrypt(encryption_keys, plainText)

# generating keys for decryption
decryption_keys = generate_decryption_key(encryption_keys)

print("\nCipherText : ", cipherText)
print("-" * 30)
Text = encrypt(decryption_keys, cipherText)

print("\nDecipherText : ", Text)

# if text after decryption matches with plaintext
if Text == plainText:
    print("Plaintext and text after decryption matches")
