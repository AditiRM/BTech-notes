from socket import *
key = 14098325
Dict = {}

#Decryption algorithm
def Decryption(cipherText, key):
    keyList =  [int(x) for x in str(key)]
    decrypted_text = []
    cipherList = []

    for f in cipherText:
        cipherList.append(ord(f))

    for p in range(len(cipherList)):
        #if position is even then subtract the key value else add
        if p % 2 == 0:
            decrypted_text.append((cipherList[p] - keyList[p % len(keyList)]))
        else:
            k = cipherList[p] + keyList[p % len(keyList)]
            if k > 126:
                decrypted_text.append(k - 127)
            else:
                decrypted_text.append(k)

    #storing back values of char
    for l in range(len(decrypted_text)):
        decrypted_text[l] = chr(decrypted_text[l])

    decryptedText = "".join(decrypted_text)
    print("Decrypted Text:", decryptedText)
    return decryptedText

serverPort = 12004
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
print('The server is ready to receive')

while(1):
    connectionSocket, addr = serverSocket.accept()
    print('new message received from: ', addr)
    #received plain text to check the validation
    mode = connectionSocket.recv(1024).decode()
    if mode == "R":
        username = connectionSocket.recv(1024).decode()
        plainText = connectionSocket.recv(1024).decode()
        Dict[username] = plainText
        print("Clients: ", Dict)
        connectionSocket.send("Registration Successful!".encode())
        print("User "+username+" Added Successfully")
    
    if mode == "L":
        username = connectionSocket.recv(1024).decode()
        plainText = connectionSocket.recv(1024).decode()
        #recieved cipher text generated from client
        sentence = connectionSocket.recv(1024).decode()
        print("\nSuccessfully Recieved Encrypted Text:", sentence)

        if username in Dict:
            decryptedText = Decryption(sentence, key)

            if Dict[username] == decryptedText:
                connectionSocket.send("AUTHENTICATION SUCCESSFUL".encode())
            else:
                connectionSocket.send("AUTHENTICATION UNSUCCESSFUL".encode())

            print("Authentication is done..")

        else:
            connectionSocket.send("Please register first".encode())
    connectionSocket.close()
