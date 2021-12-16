from socket import *
key = 14098325

#Encryption Algorithm
def encryption(plainText, key):
    keyList =  [int(x) for x in str(key)]
    cipherText = []
    for p in range(len(plainText)):
        #if position is even then add the key value else subtract
        if p % 2 == 0:
            cipherText.append((plainText[p] + keyList[p % len(keyList)]))
        else:
            k = plainText[p] - keyList[p % len(keyList)]
            if k < 0:
                cipherText.append(k + 127)
            else:
                cipherText.append(k)

    #stor ethe ascii values of characters into the list
    for l in range(len(cipherText)):
        cipherText[l] = chr(cipherText[l])

    CipherText = "".join(cipherText)
    return CipherText

serverName = "127.0.0.1"
serverPort = 12004
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

print("Enter the Option: ")
print("1: Register(R)\n2: Login(L)")

mode = input()

if mode == "R":
    clientSocket.send(mode.encode())
    username = input("Enter Username: ")
    clientSocket.send(username.encode())
    plainText = input("Enter Password: ")
    clientSocket.send(plainText.encode())

    msg = clientSocket.recv(1024).decode()
    print(msg)

if mode == "L":
    clientSocket.send(mode.encode())
    username = input("Enter Username: ")
    clientSocket.send(username.encode())
    plainText = input("Enter Password: ")
    clientSocket.send(plainText.encode())

    plainText_ASCII = []

    for char in plainText:
        plainText_ASCII.append(ord(char))

    cipherText = encryption(plainText_ASCII, key)
    print("Ciphertext: ", cipherText)
    print("\nSending Encrypted Text to Server")

    clientSocket.send(cipherText.encode())

    msg = clientSocket.recv(1024).decode()
    print(msg)

clientSocket.close()
