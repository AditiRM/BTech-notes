f = open("input.txt")
t = open("output1.txt","w")
output=""
out=""
key = int(input("enter key:"))
result = ""
while True:
    c = f.read(1)
    if not c:
        break
    if (c.isupper()):
        result += chr((ord(c) + key-65) % 26 + 65)
    elif (c.islower()):
        result += chr((ord(c) + key-97) % 26 + 97)
    else :
        continue
d=-1
for i in range(0, len(result), 5):
    d = d+1
    if not(d%10) and d!=0:
        output+="\n" 
           
           
    output+=result[i:i+5]
    output+=" "
    #print(output)
    #out+=output
    #out+="\n\n"
   


#print(out)

#print(result)
t.write(output)
        

        
