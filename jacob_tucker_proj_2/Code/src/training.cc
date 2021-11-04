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


int main(int argc, char *argv[]) {

    std::string inputFilePath;
    std::string outputSpamPath;
    std::string outputHamPath;

    const std::string prePath = "../";

    //Store each argument after flag in appropriate string.
    //Assumes working directory is build folder
    //Read and writes to parent directory
    for(int i = 0; i < argc; i++) {
        std::string temp = argv[i];
        if(strcmp( argv[i], "-i") == 0) {
            inputFilePath = prePath + argv[i + 1];
        }
        else if(strcmp( argv[i], "-os") == 0) {
            outputSpamPath = prePath + argv[i + 1];
        }
        else if(strcmp( argv[i], "-oh") == 0) {
            outputHamPath = prePath + argv[i + 1];
        }
    }

    //Two unordered maps to store strings as keys and ints values representing frequency of word found
    std::unordered_map<std::string, int> hamMap;
    std::unordered_map<std::string, int> spamMap;

    //Open input file for parsing
    std::ifstream iFile(inputFilePath);
    if(!iFile.is_open()) {
        std::cout << "Error opening file\n";
    }
    std::string line;

    //Get each line, separate line into substrings by ','.
    //If first value is ham/Spam, use correct umap
    //Check each word in second value.
    //If word already in umap, increment value
    //Else add word to umap with initial value = 1
    while(getline(iFile, line)) {

    }

    //Close input file
    iFile.close();



    return 0;

}