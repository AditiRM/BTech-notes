from typing import OrderedDict
import nltk
from nltk.corpus.reader import lin
from nltk.tokenize import word_tokenize
import glob
import re
import os
from nltk.corpus import wordnet as wn

def finding_all_unique_words(words):
    words_unique = []
    for word in words:
        if word not in words_unique:
            if word in stopwords:
                pass
            else:
                words_unique.append(word)
    return words_unique

all_words = []
unique_words_list_global = []
stopwords = set(nltk.corpus.stopwords.words('english'))
file_folder = 'test/*'
idx = 1
files_with_index = {}
for file in glob.glob(file_folder):
    fname = file
    file = open(file , "r")
    text = file.read().lower()
    text = re.sub('[^a-z\ \']+', " ", text)
    words = word_tokenize(text)
    words = [word for word in words if len(words)>1]
    words = [word.lower() for word in words]
    unique_words_list_global = set().union(unique_words_list_global, finding_all_unique_words(words))
    files_with_index[idx] = os.path.basename(fname)
    idx = idx + 1
print(files_with_index)


linked_list = {}
for word in unique_words_list_global:
    linked_list[word] = []

idx = 1
for file in glob.glob(file_folder):
    file = open(file, "r")
    text = file.read()
    words = word_tokenize(text)
    words = [word for word in words if len(words)>1]
    words = [word.lower() for word in words]
    word_in_doc = finding_all_unique_words(words)
    for word in unique_words_list_global:
        if word in word_in_doc:
            linked_list[word].append(1)
        else:
            linked_list[word].append(0)
    idx = idx + 1

linked_list = OrderedDict(sorted(linked_list.items()))
for element in linked_list:
    print(element, "\t", linked_list[element])
print()


def solve_list(word_list, boolean_operators):
    zeroes_and_ones_of_all_words = []
    current_word_zeros_and_ones = []
    for word in word_list:
        if word in unique_words_list_global:
            current_word_zeros_and_ones = linked_list[word]
        else:
            current_word_zeros_and_ones = [0, 0, 0, 0, 0]
#      Synonym addition
        unique_synonyms = []
        for synsnet in wn.synsets(word):
            for synonym in synsnet.lemmas():
                if synonym.name() not in unique_synonyms:
                    unique_synonyms.append(synonym.name())
        for synonym in unique_synonyms:
            if synonym in unique_words_list_global:
                current_word_zeros_and_ones = [w1 | w2 for (w1,w2) in zip(current_word_zeros_and_ones, linked_list[synonym])]
        
        zeroes_and_ones_of_all_words.append(current_word_zeros_and_ones)
    
    temp_zeros_and_ones = solve_zeros_and_ones(zeroes_and_ones_of_all_words, boolean_operators)
    print(temp_zeros_and_ones)
    print()
    return temp_zeros_and_ones

def solve_zeros_and_ones(zeroes_and_ones_of_all_words, boolean_operators):
    if len(zeroes_and_ones_of_all_words) == 0:
        return zeroes_and_ones_of_all_words
    elif len(zeroes_and_ones_of_all_words) == 1:
        return zeroes_and_ones_of_all_words[0]
    for word in zeroes_and_ones_of_all_words:
        print(word)
    print("Boolean operators : ", boolean_operators)
    for word in boolean_operators:
        word_list1 = zeroes_and_ones_of_all_words[0]
        word_list2 = zeroes_and_ones_of_all_words[1]
        if word == "and":
            bitwise_op = [w1 & w2 for (w1,w2) in zip(word_list1,word_list2)]
            zeroes_and_ones_of_all_words.remove(word_list1)
            zeroes_and_ones_of_all_words.remove(word_list2)
            zeroes_and_ones_of_all_words.insert(0, bitwise_op)
        elif word == "or":
            bitwise_op = [w1 | w2 for (w1,w2) in zip(word_list1,word_list2)]
            zeroes_and_ones_of_all_words.remove(word_list1)
            zeroes_and_ones_of_all_words.remove(word_list2)
            zeroes_and_ones_of_all_words.insert(0, bitwise_op)
        elif word == "not":
            bitwise_op = [not w1 for w1 in word_list2]
            bitwise_op = [int(b == True) for b in bitwise_op]
            zeroes_and_ones_of_all_words.remove(word_list2)
            zeroes_and_ones_of_all_words.remove(word_list1)
            bitwise_op = [w1 & w2 for (w1,w2) in zip(word_list1,bitwise_op)]
    zeroes_and_ones_of_all_words.insert(0, bitwise_op)
    
    return zeroes_and_ones_of_all_words[0]


def print_final_files(ans):
    files = []
    zeroes_and_ones_of_file = ans
    print("Final zeros and one's of files -> ", zeroes_and_ones_of_file)

    cnt = 1
    for index in zeroes_and_ones_of_file:
        if index == 1:
            files.append(files_with_index[cnt])
        cnt = cnt+1
    print(files)

query = input('Enter query : ')
query = word_tokenize(query)
paranthesis_open = ['(', '[', '{']
paranthesis_close = {'(' : ')', '[' : ']', '{' : '}'}
paranthesis_stack = []
query_words = ['and', 'or', 'not']
boolean_operators = []
final_words_list = []
final_zeros_and_ones_list = []

for word in query:
    if word in paranthesis_open:
        paranthesis_stack.append(word)
    elif word in paranthesis_close.values():
        if len(paranthesis_stack) > 0:
            if  word == paranthesis_close[paranthesis_stack[-1]]:
                paranthesis_stack.pop()
            else:
                print("Incorrect paranthesis")
                exit()
        else:
            print("Incorrect paranthesis")
            exit()

if len(paranthesis_stack) > 0:
    print("Incorrect paranthesis")
    exit()

solve_paranthesis_stack = []
operation_paranthesis_stack = []
in_paranthesis = False
word_zeros_and_ones = []

for word in query:
    if word in paranthesis_open:
        in_paranthesis = True
    elif word in paranthesis_close.values():
        in_paranthesis = False
        final_zeros_and_ones_list.append(solve_list(solve_paranthesis_stack, operation_paranthesis_stack))
        operation_paranthesis_stack.clear()
        solve_paranthesis_stack.clear()
    else:
        if in_paranthesis:
            if word.lower() in query_words:
                operation_paranthesis_stack.append(word.lower())
            else:
                solve_paranthesis_stack.append(word)
        else:
            if word.lower() in query_words:
                boolean_operators.append(word.lower())
            else:
                if word in unique_words_list_global:
                    current_word_zeros_and_ones = linked_list[word]
                else:
                    current_word_zeros_and_ones = [0, 0, 0, 0, 0]
        #       Synonym addition
                unique_synonyms = []
                for synsnet in wn.synsets(word):
                    for synonym in synsnet.lemmas():
                        if synonym.name() not in unique_synonyms:
                            unique_synonyms.append(synonym.name())
                for synonym in unique_synonyms:
                    if synonym in unique_words_list_global:
                        current_word_zeros_and_ones = [w1 | w2 for (w1,w2) in zip(current_word_zeros_and_ones, linked_list[synonym])]
                
                final_zeros_and_ones_list.append(current_word_zeros_and_ones)

ans = solve_zeros_and_ones(final_zeros_and_ones_list, boolean_operators)

print()
print_final_files(ans)
