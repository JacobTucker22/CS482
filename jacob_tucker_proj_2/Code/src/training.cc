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

    return 0;

}