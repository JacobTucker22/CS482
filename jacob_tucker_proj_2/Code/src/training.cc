//
// Created by jtucker on 11/3/21.
//

//Notes
//Get file path from args
//Store file paths
//create two umaps ham spam
//store each new string in umap with 1 (maybe zero, might clean out low freq strings before write to file)
//increment each recurring string found in respective umap
//keep track of total number of words (in umap? maybe first entry in umap "total words" no other entry should have a space
//write to file given in args. csv with total words, and freq count of each word

#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[]) {
    if (argc != 7) {
        cout << "Correct Usage: ./training -i <input file.csv> -os <spam output file.csv> -oh <ham output file.csv>\n"
                "Order of arguments does not matter as long as correct flags are in front of file paths\n";
        return 1;
    }

    //read write file paths
    string inputFilePath;
    string outputSpamPath;
    string outputHamPath;

    //Count of total number of words in each class
    int *totalWordsPtr;
    int totalHamWords = 0;
    int totalSpamWords = 0;

    //prepended to file paths so it writes in main folder instead of build
    const string prePath = "../";

    //Store each argument after flag in appropriate string.
    //Assumes working directory is build folder
    //Read and writes to parent directory
    for (int i = 0; i < argc; i++) {
        string temp = argv[i];
        if (strcmp(argv[i], "-i") == 0) {
            inputFilePath = prePath + argv[i + 1];
        } else if (strcmp(argv[i], "-os") == 0) {
            outputSpamPath = prePath + argv[i + 1];
        } else if (strcmp(argv[i], "-oh") == 0) {
            outputHamPath = prePath + argv[i + 1];
        }
    }

    //Two unordered maps to store strings as keys and ints values representing frequency of word found
    //Ptr points to which umap is being used at each line
    unordered_map<string, int> *uMapPtr = nullptr;
    unordered_map<string, int> hamMap;
    unordered_map<string, int> spamMap;

    //Open input file for parsing
    ifstream iFile(inputFilePath);
    if (!iFile.is_open()) {
        cout << "Error opening input file\n";
        return 1;
    }
    string line;

    //Ignore the top columns
    getline(iFile, line);

    //Get each line, separate line into substrings by ','.
    //If first value is ham/Spam, use correct umap
    //Check each word in second value.
    //If word already in umap, increment value
    //Else add word to umap with initial value = 1
    while (getline(iFile, line)) {
        stringstream ssLine(line);

        //Holds value for type classification
        string type;
        //Get type from first column and set umap ptr
        getline(ssLine, type, ',');
        if (type == "ham") {
            uMapPtr = &hamMap;
            totalWordsPtr = &totalHamWords;
        } else if (type == "spam") {
            uMapPtr = &spamMap;
            totalWordsPtr = &totalSpamWords;
        } else {
            cout << "Unrecognized class type. Please use ham or spam\n";
        }

        //holds the string of word data
        string data;
        //Get data from second column
        getline(ssLine, data);

        //clean data. Remove punctuation and make lower case
        data.erase(remove_if(data.begin(), data.end(), ::ispunct), data.end());
        transform(data.begin(), data.end(), data.begin(), ::tolower);

        //make stream of clean data for parsing
        //Consider removing single character words (may not be helpful for classification)
        stringstream ssData(data);
        string word;
        while (true) {
            ssData >> word;
            //increment total words for ham or spam
            *totalWordsPtr = *totalWordsPtr + 1;
            //check for value, increment count if it exists, or add with value = 1
            auto it = uMapPtr->find(word);
            if (it != uMapPtr->end()) {
                it->second++;
            } else {
                uMapPtr->insert(make_pair(word, 1));
            }
            if (ssData.eof()) {
                break;
            }
        }
    }
    //Close input file. Done reading from file
    iFile.close();

    //Open Ham file and write values
    ofstream outHamFile(outputHamPath);
    if (!outHamFile.is_open()) {
        cout << "Error opening output ham file\n";
        return 1;
    }
    outHamFile << totalHamWords << "\n";

    for (const auto it: hamMap) {
        outHamFile << it.first << ','
                   << it.second << "\n";
    }
    outHamFile.close();

    //Open Spam file and write values
    ofstream outSpamFile(outputSpamPath);
    if (!outSpamFile.is_open()) {
        cout << "Error opening output spam file\n";
        return 1;
    }
    outSpamFile << totalSpamWords << "\n";

    for (const auto it: spamMap) {
        outSpamFile << it.first << ','
                    << it.second << "\n";
    }
    outSpamFile.close();

    return 0;

}