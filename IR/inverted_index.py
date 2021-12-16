from typing import OrderedDict
import nltk
from nltk.tokenize import word_tokenize
import glob
import re
import os

def find_unique(words):
    unique_w = []
    for word in words:
        if word not in unique_w:
            if word in stopwords:
                pass
            else:
                unique_w.append(word)
    return unique_w

all_words = []
global_unique_w = []
stopwords = set(nltk.corpus.stopwords.words('english'))
file_folder = 'files/*'
idx = 1
files_with_index = {}
for file in glob.glob(file_folder):
    fname = file
    file = open(file , "r")
    text = file.read()
    text = re.sub('[^a-z\ \']+', " ", text)
    words = word_tokenize(text)
    words = [word for word in words if len(words)>1]
    words = [word.lower() for word in words]
    global_unique_w = set().union(global_unique_w, find_unique(words))
    files_with_index[idx] = os.path.basename(fname)
    idx = idx + 1

linklist = {}
for word in global_unique_w:
    linklist[word] = []

idx = 1
for file in glob.glob(file_folder):
    file = open(file, "r")
    text = file.read()
    text = re.sub('[^a-z\ \']+', " ", text)
    words = word_tokenize(text)
    words = [word for word in words if len(words)>1]
    words = [word.lower() for word in words]
    word_in_doc = find_unique(words)
    for word in global_unique_w:
        if word in word_in_doc:
            linklist[word].append(idx)
        else:
            pass
    idx = idx + 1
print(files_with_index)

linklist = OrderedDict(sorted(linklist.items()))
for ele in linklist:
    print(ele, "\t", linklist[ele])
print()


def solve_list(w_list, bool_op):
    all_zero_ones = []
    for word in w_list:
        if word in global_unique_w:
            all_zero_ones.append(linklist[word])
        else:
            pass
    zero_ones_temp = solve_zero_ones(all_zero_ones, bool_op)
    print(zero_ones_temp)
    print()
    return zero_ones_temp

def solve_zero_ones(all_zero_ones, bool_op):
    if len(all_zero_ones) == 0:
        return all_zero_ones
    elif len(all_zero_ones) == 1:
        return all_zero_ones[0]
    for word in all_zero_ones:
        print(word)
    print("Boolean operators : ", bool_op)
    for word in bool_op:
        w_list1 = all_zero_ones[0]
        w_list2 = all_zero_ones[1]
        if word == "and":
            all_zero_ones.insert(0, list(set(w_list1) & set(w_list2)))
            all_zero_ones.remove(w_list1)
            all_zero_ones.remove(w_list2)
        elif word == "or":
            all_zero_ones.insert(0, list(set(w_list1) | set(w_list2)))
            all_zero_ones.remove(w_list1)
            all_zero_ones.remove(w_list2)
        elif word == "not":
            all_zero_ones.insert(0, list(set(w_list1) - set(w_list2)))
            all_zero_ones.remove(w_list1)
            all_zero_ones.remove(w_list2)

    
    return all_zero_ones[0]

def print_files(ans):
    files = []
    zero_ones_in_files = ans
    print("All zeros and one's of files -> ", zero_ones_in_files)

    cnt = 1
    for index in zero_ones_in_files:
        files.append(files_with_index[index])
    print(files)

query = input('Enter the query: ')
query = word_tokenize(query)
brackets_op = ['(', '[', '{']
brackets_cl = {'(' : ')', '[' : ']', '{' : '}'}
brackets_stack = []
query_w = ['and', 'or', 'not']
bool_op = []
final_words_list = []
zero_ones_final_list = []

# checking if brackets are used correctly
for word in query:
    if word in brackets_op:
        brackets_stack.append(word)
    elif word in brackets_cl.values():
        if len(brackets_stack) > 0:
            if  word == brackets_cl[brackets_stack[-1]]:
                brackets_stack.pop()
            else:
                print("Incorrect paranthesis")
                exit()
        else:
            print("Incorrect paranthesis")
            exit()

if len(brackets_stack) > 0:
    print("Incorrect paranthesis")
    exit()

solve_brackets_stack = []
brackets_stack_operations = []
in_paranthesis = False
w_zero_ones = []

for word in query:
    if word in brackets_op:
        in_paranthesis = True
    elif word in brackets_cl.values():
        in_paranthesis = False
        zero_ones_final_list.append(solve_list(solve_brackets_stack, brackets_stack_operations))
        brackets_stack_operations.clear()
        solve_brackets_stack.clear()
    else:
        if in_paranthesis:
            if word.lower() in query_w:
                brackets_stack_operations.append(word.lower())
            else:
                solve_brackets_stack.append(word)
        else:
            if word.lower() in query_w:
                bool_op.append(word.lower())
            else:
                if word in global_unique_w:
                    zero_ones_final_list.append(linklist[word])
                else:
                    zero_ones_final_list.append([])
                    pass

ans = solve_zero_ones(zero_ones_final_list, bool_op)

print()
print_files(ans)
