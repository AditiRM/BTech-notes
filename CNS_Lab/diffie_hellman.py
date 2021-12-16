# Return (a^b Mod c)
def computeMod(a, b, c):
    return int(pow(a, b, c))


# Publicly available keys. P is any prime number and G is any primitive root of P.
P = 31
G = 24

# 2 Private keys
a = int(input("Enter private key a: "))
b = int(input("Enter private key b: "))

# Generated Keys
x = computeMod(G, a, P)
y = computeMod(G, b, P)

print("\nGenerated public keys are:")
print("x: ", x)
print("y: ", y)

# Secret Keys
print("\nSecret keys according to diffie-hellman algorithm are:")
Ka = computeMod(y, a, P)
Kb = computeMod(x, b, P)

print("Secret key Ka:", Ka)
print("Secret key Kb:", Kb)
