//
// Created by jtucker on 11/3/21.
//

#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 9) {
        cout << "Correct Usage: ./classify -i <data to test.csv> -is <spam output file from training.csv> "
                "-ih <ham output file from training.csv> -o <output file path.csv>\n"
                "Order of arguments does not matter as long as correct flags are in front of file paths\n";
        return 1;
    }

    //prepended to file paths so it writes in main folder instead of build
    const string prePath = "../";

    //read write file paths
    string inputDataPath;
    string inputSpamPath;
    string inputHamPath;
    string outputPath;

    //Store each argument after flag in appropriate string.
    //Assumes working directory is build folder
    //Read and writes to parent directory
    for(int i = 0; i < argc; i++) {
        string temp = argv[i];
        if(strcmp( argv[i], "-i") == 0) {
            inputDataPath = prePath + argv[i + 1];
        }
        else if(strcmp( argv[i], "-is") == 0) {
            inputSpamPath = prePath + argv[i + 1];
        }
        else if(strcmp( argv[i], "-ih") == 0) {
            inputHamPath = prePath + argv[i + 1];
        }
        else if(strcmp( argv[i], "-o") == 0) {
            outputPath = prePath + argv[i + 1];
        }
    }


    return 0;

}