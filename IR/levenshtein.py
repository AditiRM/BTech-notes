import numpy as np

def levenshtein(source, target):  
    size_x = len(source) + 1 # + 1 for the empty first position
    size_y = len(target) + 1
    #matrix
    matrix = np.zeros ((size_x, size_y)) #initializing with zeros
    for x in range(size_x):
        matrix [x, 0] = x   #initializing first row
    for y in range(size_y):
        matrix [0, y] = y   #initializing first column
    #computing the levenshtein distance
    for x in range(1, size_x):
        for y in range(1, size_y):
            if source[x-1] == target[y-1]:     
                edit = 0                    
            else:
                edit = 1
            x1y = matrix[x-1,y] + 1         #[x - 1, y] //cell left of current
            x1y1 = matrix[x-1,y-1] + edit   #[x - 1, y - 1] // cell dig to current
            xy1 = matrix[x,y-1] + 1         #[x, y - 1] //cell above current
            matrix [x,y] = min(x1y, x1y1, xy1)
    print(matrix)
    return (matrix[size_x - 1, size_y - 1])


def main():
    s_str = input("Enter the source string :: ")
    t_str = input("Enter the target string :: ")

    print('Levenshtein distance for provided source and target string is :: ', levenshtein(s_str,t_str))

if __name__ == "__main__":
    main()
    