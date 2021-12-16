cipherText = input("Enter the Cipher Text: ").upper()
key = input("Enter the key: ").upper()

LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!'


keyMatrix = [[0] * 3 for i in range(3)] 
k = 0

for i in range(3):
    for j in range(3):
        keyMatrix[i][j] = LETTERS.find(key[k])
        k = k+1

det = keyMatrix[0][0]*(keyMatrix[1][1]*keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) - keyMatrix[0][1]*(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) + keyMatrix[0][2]*(keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0])

for x in range(1, 29):
    if (((det%29) * (x%29)) % 29 == 1):
        mul_inv = x


keyInverse = [[0] * 3 for i in range(3)] 

keyInverse[0][0] = int((keyMatrix[1][1]*keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]))
keyInverse[0][1] = int(-1 * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]))
keyInverse[0][2] = int((keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]))
keyInverse[1][0] = int(-1 * (keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]))
keyInverse[1][1] = int((keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]))
keyInverse[1][2] = int(-1 * (keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]))
keyInverse[2][0] = int((keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[1][1] * keyMatrix[0][2]))
keyInverse[2][1] = int(-1 * (keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[1][0] * keyMatrix[0][2]))
keyInverse[2][2] = int((keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[1][0] * keyMatrix[0][1]))

keyInverse = [[keyInverse[j][i] for j in range(len(keyInverse))] for i in range(len(keyInverse[0]))]

for i in range(3):
    for j in range(3):
        keyInverse[i][j] = keyInverse[i][j] * mul_inv

size_message = int(len(cipherText) / 3)
CipherMatrix = [[0] * size_message for i in range(3)]

k = 0
j = 0
while(k < size_message):
    for i in range(3):
        CipherMatrix[i][k] = LETTERS.find(cipherText[j])
        j = j + 1
    k = k + 1

plainMatrix = [[0] * size_message for i in range(3)]

for i in range(3):
    for j in range(size_message):
        plainMatrix[i][j] = 0
        for x in range(3):
            
            plainMatrix[i][j] += (keyInverse[i][x] * CipherMatrix[x][j])
        
        plainMatrix[i][j] = plainMatrix[i][j] % 29


PlainText = []

k = 0
while(k < size_message):
    for i in range(3):
        num = plainMatrix[i][k]
        PlainText.append(LETTERS[num])
    k = k + 1

print("Plaintext:", "".join(PlainText))