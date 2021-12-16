import nltk
from nltk.corpus import wordnet
import itertools

def synonyms(query):
    synonyms = []

    for syn in wordnet.synsets(query):
        for l in syn.lemmas():
            synonyms.append(l.name())
    
    count = len(synonyms)
    print("All the synonyms for the given word query are >>> ",synonyms)
    print("\t")
    print("Total no. of synonyms for word " + query + " are >>> " + str(count))
    print("\t")

def antonyms(query):
    antonyms = []
    for syn in wordnet.synsets(query):
        for l in syn.lemmas():
            if l.antonyms():
                antonyms.append(l.antonyms()[0].name())

    print("All the antonyms for the given word query are >>> ",antonyms)
    print("\t")

def hyponyms(query):
    hyponyms = []

    for syn in wordnet.synsets(query):
        for l in syn.hyponyms():
             hyponyms.append(l.lemma_names())
 
    print("All the hyponyms for the given word query are >>> ", hyponyms)
    print("\t")

def hypernyms(query):
    hypernyms = []

    for syn in wordnet.synsets(query):
        for l in syn.hypernyms():
             hypernyms.append(l.lemma_names())
 
    print("All the hypernyms for the given word query are >>> ", hypernyms)
    print("\t")

def co_hyponyms(query):
    unique_hypernyms = []
    for synsnet in wordnet.synsets(query):
        for hypernyms in synsnet.hypernyms():
            if hypernyms not in unique_hypernyms:
               unique_hypernyms.append(hypernyms)

    print("\nCo hyponyms for ", query, " are : ", end="\n")
    unique_co_hyponyms = []
    for synsnet in unique_hypernyms:
        for co_hyponyms in synsnet.hyponyms():
            if co_hyponyms not in unique_co_hyponyms:
                unique_co_hyponyms.append(co_hyponyms)
    print(unique_co_hyponyms)
    print("")

def meaning(query):
    print("All the meanings for the given word are:: ")
    for syn in (wordnet.synsets(query)):
        print (syn.name() + " >>> " + syn.definition())
    print("\t")

def no_of_senses(query):
    all_senses = []
    
    for syn in (wordnet.synsets(query)):
        all_senses.append(syn.name())

    l = len(all_senses)
    print("No .of senses of the given word in all parts-of-speech are:: "+ str(l) + "\t")

def sports_domain(min_similarity=0.75):
    for word in wordnet.words():
        syn1 = wordnet.synsets("sport")[0]
        syn2 = wordnet.synsets(word)[0]
        similarity = syn1.wup_similarity(syn2)
        if similarity > min_similarity:
            print(word, similarity)

def all_nouns():
    file1 = open("all_nouns.txt", "a")
    all = []
    for syn in list(wordnet.all_synsets('n')):
        all.append(syn.name())

    l = len(all)
    for i in range(l):
        file1.write(all[i])
        file1.write("\n")

    file1.close()   


def one_word_query():
    query = input("Enter the word to run query for:: ")
    print("\n")
    synonyms(query)
    
    antonyms(query)

    hyponyms(query)

    hypernyms(query)

    co_hyponyms(query)

    meaning(query)

    no_of_senses(query)

    all_nouns()

    


def semantic_similarity():

    f_word = input("Enter the first word:: ")
    s_word = input("Enter the second word:: ")

    syn1 = wordnet.synsets(f_word)[0]
    syn2 = wordnet.synsets(s_word)[0]

    print("The semantic similarity between the words is :: ",syn1.wup_similarity(syn2))


while(1):
    choice = int(input("\n1.Single Word Query\n2.Semantic Similarity\n3.Sport Domain\n4.Exit\nEnter query type no.: "))
    if choice == 1:
        one_word_query()
    elif choice == 2:
        semantic_similarity()
    elif choice == 3:
        sports_domain()
    elif choice == 4:
        exit()
    else:
        print("Choose correct option")
