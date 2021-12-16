
def search(keyT, a, b, arr):
    if(a == 'j'):
        a = 'i'
    elif(b == 'j'):
        b = 'i'
    for i in range(5):
        for j in range(5):
            if(keyT[i][j] == a):
                arr[0] = i
                arr[1] = j
            elif(keyT[i][j] == b):
                arr[2] = i
                arr[3] = j

plainText = input("Enter plain text: ").lower()
key = input("Enter the key: ").lower()

plainText = "".join(u for u in plainText if u not in (" "))
key = "".join(u for u in key if u not in (" "))

if(len(plainText) %2 != 0):
    plainText += 'z'


keyTable = [[0] * 5 for i in range(5)]


chars = [0]*26
for i in range(len(key)):
    if(key[i] != 'j'):
        chars[ord(key[i]) - 97] = 2

chars[ord('j') - 97] = 1

i = 0
j = 0

for k in range(len(key)):
    if(chars[ord(key[k]) - 97] == 2):
        chars[ord(key[k]) - 97] -= 1
        keyTable[i][j] = key[k]
        j += 1
        if(j == 5):
            i += 1
            j = 0

for k in range(26):
    if(chars[k] == 0):
        keyTable[i][j] = chr(k+97)
        j += 1
        if(j == 5):
            i += 1
            j = 0


print("Key Matrix is:")
for i in range(5):
    for j in range(5):
        print(keyTable[i][j], end = "\t")
    print()


a = [0]*4
i = 0
cipher = [0]*len(plainText)
cipherText = ""

while(i < len(plainText)):
    search(keyTable, plainText[i], plainText[i+1], a)

    if (a[0] == a[2]):
        cipher[i] = keyTable[a[0]][(a[1] + 1)%5]
        cipher[i + 1] = keyTable[a[0]][(a[3] + 1)%5]
    
    elif(a[1] == a[3]):
        cipher[i] = keyTable[(a[0] + 1)%5][a[1]]
        cipher[i + 1] = keyTable[(a[2] + 1)%5][a[1]]
    
    else:
        cipher[i] = keyTable[a[0]][a[3]]
        cipher[i + 1] = keyTable[a[2]][a[1]]

    i = i + 2

for y in cipher: 
    cipherText += y
    
print("Cipher Text : ", cipherText)