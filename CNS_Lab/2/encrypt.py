plainText = input("Enter the Plain Text: ").upper()
key = input("Enter the key: ").upper()

plainText = "".join(u for u in plainText if u not in ("?", " ", ";", ":", "/", "[", "]"))
x = len(plainText)%3
if(x!=0):
    for i in range(3-x):
        plainText += 'X'

LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!'


keyMatrix = [[0] * 3 for i in range(3)] 
k = 0

for i in range(3):
    for j in range(3):
        keyMatrix[i][j] = LETTERS.find(key[k])
        k = k+1


size_message = int(len(plainText) / 3)
messageMatrix = [[0] * size_message for i in range(3)]

k = 0
j = 0
while(k < size_message):
    for i in range(3):
        messageMatrix[i][k] = LETTERS.find(plainText[j])
        j = j + 1
    k = k + 1


cipherMatrix = [[0] * size_message for i in range(3)]

for i in range(3):
    for j in range(size_message):
        cipherMatrix[i][j] = 0
        for x in range(3):
            
            cipherMatrix[i][j] += (keyMatrix[i][x] * messageMatrix[x][j])
       
        cipherMatrix[i][j] = cipherMatrix[i][j] % 29


CipherText = []

k = 0
while(k < size_message):
    for i in range(3):
        num = cipherMatrix[i][k]
        CipherText.append(LETTERS[num])
    k = k + 1

print("Ciphertext:", "".join(CipherText))

