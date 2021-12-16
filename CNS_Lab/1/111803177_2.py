f = open("output1.txt")
result = ""
out = ""
key=1
t = open("output2.txt","w")
while key<=25:
   
    
    f = open("output1.txt")
   
    result = ""
    while True:
        c = f.read(1)
        if not c:
            break
        if (c.isupper()):
            result += chr((ord(c) - key-65) % 26 + 65)
        elif (c.islower()):
            result += chr((ord(c) - key-97) % 26 + 97)
        else :
            continue
    #print(result)
    d=-1
    output = ""
    output+="Key: "
    output+=str(key)
    output+="\n" 
    for i in range(0, len(result), 5):
       
        d = d+1
        if not(d%10) and d!=0:
            output+="\n" 
           
           
        output+=result[i:i+5]
        output+=" "
    #print(output)
    out+=output
    out+="\n\n"
    key=key+1


#print(out)

#print(result)
t.write("Cryptaanalyis for the above(outut1.txt):  \n")
t.write(out)
        
