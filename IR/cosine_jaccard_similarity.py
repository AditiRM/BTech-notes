import nltk
from os import listdir
from os.path import isfile, join
from nltk.util import pr
from numpy import square
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import re
import math

# All docs to sompare
# BASE_INPUT_DIR = "./files"
N = 3

def returnListOfFilePaths(folderPath):
    fileInfo = []
    listOfFileNames = [fileName for fileName in listdir(folderPath) if isfile(join(folderPath, fileName))]
    listOfFilePaths = [join(folderPath, fileName) for fileName in listdir(folderPath) if isfile(join(folderPath, fileName))]
    fileInfo.append(listOfFileNames)
    fileInfo.append(listOfFilePaths)
    return fileInfo

#raw data creation
def create_docContentDict(filePaths):
    rawContentDict = {}
    for filePath in filePaths:
        with open(filePath, "r") as ifile:
            fileContent = ifile.read()
        rawContentDict[filePath] = fileContent
    return rawContentDict

#tokenization
def tokenizeContent(contentsRaw):
    contents_regexed = re.sub('[^a-zA-Z\ \']+', " ", contentsRaw)
    tokenized = nltk.tokenize.word_tokenize(contents_regexed)
    return tokenized

#removing stopwords
def removeStopWordsFromTokenized(contentsTokenized):
    stop_word_set = set(nltk.corpus.stopwords.words('english'))
    # print(stop_word_set)
    filteredContents = [word for word in contentsTokenized if word not in stop_word_set]
    return filteredContents

#stemming
def performPorterStemmingOnContents(contentsTokenized):
    porterStemmer = nltk.stem.PorterStemmer()
    filteredContents = [porterStemmer.stem(word) for word in contentsTokenized]
    return filteredContents

#changing to lower case
def convertItemsToLower(contentsRaw):
    filteredContents = [term.lower() for term in contentsRaw]
    return filteredContents

# process data without writing inspection file information to file
def processData(rawContents):
    cleaned = tokenizeContent(rawContents)
    cleaned = removeStopWordsFromTokenized(cleaned)
    cleaned = performPorterStemmingOnContents(cleaned)    
    cleaned = convertItemsToLower(cleaned)
    return cleaned

def calc_jaccard_similarity(word_dict, doc1, doc2):
    numValue = len(list(set(word_dict[doc1]) & set(word_dict[doc2]))) / len(list(set(word_dict[doc1]) | set(word_dict[doc2])))
    print("Between", doc1, "and", doc2, "is ->", numValue)

def calc_and_print_JaccardSimilarity_for_all(word_dict, fileNames):
    print("\nJaccard SIMILARITY : \n")
    numFiles = len(fileNames)
    names = []

    calc_jaccard_similarity(word_dict, fileNames[0], fileNames[1])
    calc_jaccard_similarity(word_dict, fileNames[1], fileNames[2])
    calc_jaccard_similarity(word_dict, fileNames[0], fileNames[2])

    print()    

def tf(fileNames, word_dict, raw_dict, file_map):
    tf_dict = {}
    for key in word_dict:
        tf_dict[key] = {}
    

    numFiles = len(fileNames)
    for n in range(numFiles):
        for word in word_dict[fileNames[n]]:
            word_count = (raw_dict[file_map[n]]).count(word)
            if word_count != 0:
                tf_dict[fileNames[n]][word] = 1 + math.log10(word_count)
            else:
                tf_dict[fileNames[n]][word] = 0
    return tf_dict

def idf(fileNames, word_dict, unique_word_list):
    idf_dict = {}
    numFiles = len(fileNames)
    for word in unique_word_list:
        count = 0
        for n in range(numFiles):
            if word in word_dict[fileNames[n]]:
                count += 1
        if count == 0:
            idf_dict[word] = 0
        else:
            idf_dict[word] = math.log10(N/count + 1)

    return idf_dict

def tf_idf(fileNames, tf_dict, idf_dict, unique_word_list):
    tf_idf_dict = {}
    numFiles = len(fileNames)
    for n in range(numFiles):
        tf_idf_dict[fileNames[n]] = {}
        for word in unique_word_list:
            if word in tf_dict[fileNames[n]]:
                tf_idf_dict[fileNames[n]][word] = tf_dict[fileNames[n]][word] * idf_dict[word]
            else:
                tf_idf_dict[fileNames[n]][word] = 0

    return tf_idf_dict

def calc_cosine_similarity(doc1, doc2, tf_idf_dict, unique_word_list):
    num = 0
    den = 1
    norm_1 = 0
    norm_2 = 0
    for word in unique_word_list:
        num += tf_idf_dict[doc1][word] * tf_idf_dict[doc2][word]
        norm_1 += square(tf_idf_dict[doc1][word])
        norm_2 += square(tf_idf_dict[doc2][word])

    norm_1 = math.sqrt(norm_1)
    norm_2 = math.sqrt(norm_2)
    den = norm_1 * norm_2

    cosine_similarity = num / den
    print("Between", doc1, "and", doc2, "is ->", cosine_similarity)


def calc_and_print_CosineSimilarity_for_all(fileNames, word_dict, unique_word_list, rawContentDict, file_map):
        tf_dict = tf(fileNames, word_dict, rawContentDict, file_map)
        idf_dict = idf(fileNames, word_dict, unique_word_list)
        tf_idf_dict = tf_idf(fileNames, tf_dict, idf_dict, unique_word_list)

        print("\nCosine SIMILARITY : \n")

        calc_cosine_similarity(fileNames[0], fileNames[1], tf_idf_dict, unique_word_list)
        calc_cosine_similarity(fileNames[1], fileNames[2], tf_idf_dict, unique_word_list)
        calc_cosine_similarity(fileNames[0], fileNames[2], tf_idf_dict, unique_word_list)

def process_raw_dict_to_list(rawContentDict):
    for key in rawContentDict:
        contents_regexed = re.sub('[^a-zA-Z\ \']+', " ", rawContentDict[key])
        contents_lower = contents_regexed.lower()
        porterStemmer = nltk.stem.PorterStemmer()
        contents_stemmed = []
        contents_stemmed.append(" ".join([porterStemmer.stem(i) for i in contents_lower.split()]))
        rawContentDict[key] = contents_stemmed[0]

    return rawContentDict

def main(printResults=True):
    baseFolderPath = "./files/"

    fileNames, filePathList = returnListOfFilePaths(baseFolderPath)

    rawContentDict = create_docContentDict(filePathList)
    
    word_dict = {}
    file_map = {}
    unique_word_list = []
    i = 0

    rawContentDict = process_raw_dict_to_list(rawContentDict)


    for key in rawContentDict:
        word_dict[fileNames[i]] = processData(rawContentDict[key])
        file_map[i] = key
        i += 1

    for word_list in word_dict.values():
        for word in word_list:
            if word not in unique_word_list:
                unique_word_list.append(word)

    if printResults:
        calc_and_print_CosineSimilarity_for_all(fileNames, word_dict, unique_word_list, rawContentDict, file_map)

        calc_and_print_JaccardSimilarity_for_all(word_dict, list(word_dict.keys()))



if __name__ == "__main__":
    main()