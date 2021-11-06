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
#include <iomanip>

using namespace std;

//Function for reading the input files.
//Takes the ifstream for the file to be read, the unordered map to populate with the data,
//and a total words int to store the total number of words
void readFile(ifstream &iFile, unordered_map<string, int> &uMap, double &totalWords) {
    string line;
    //get total word count
    getline(iFile, line);
    totalWords = stoi(line);

    while (getline(iFile, line)) {
        stringstream ssLine(line);
        string word;
        string tempFreq;
        int freq;

        //Parse line into word and frequency value
        getline(ssLine, word, ',');
        getline(ssLine, tempFreq);
        freq = stoi(tempFreq);

        //Insert word/freq pair into ham umap
        uMap.insert(make_pair(word, freq));

    }
}

int main(int argc, char *argv[]) {
    if (argc != 9) {
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
    for (int i = 0; i < argc; i++) {
        string temp = argv[i];
        if (strcmp(argv[i], "-i") == 0) {
            inputDataPath = prePath + argv[i + 1];
        } else if (strcmp(argv[i], "-is") == 0) {
            inputSpamPath = prePath + argv[i + 1];
        } else if (strcmp(argv[i], "-ih") == 0) {
            inputHamPath = prePath + argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            outputPath = prePath + argv[i + 1];
        }
    }

    //Read in each file. Save number of ham words and spam words
    //Save word and frequencies in umaps
    unordered_map<string, int> hamMap;
    unordered_map<string, int> spamMap;
    double totalHamWords;
    double totalSpamWords;

    //Open ham input file for parsing
    ifstream iFile(inputHamPath);
    if (!iFile.is_open()) {
        cout << "Error opening ham input file\n";
        return 1;
    }
    readFile(iFile, hamMap, totalHamWords);

    iFile.close();

    //Open Spam input file for parsing
    iFile.open(inputSpamPath);
    if (!iFile.is_open()) {
        cout << "Error opening spam input file\n";
        return 1;
    }
    readFile(iFile, spamMap, totalSpamWords);

    iFile.close();


    //variables needed for algorithm
    double probHamClass = totalHamWords / (totalHamWords + totalSpamWords);
    double probSpamClass = totalSpamWords / (totalHamWords + totalSpamWords);
    double spamSize = spamMap.size();
    double hamSize = hamMap.size();
    double totalUniqueWords = hamSize + spamSize;

    //used to check the accuracy of algorithm
    float totalMessages = 0;
    float numCorrectClasses = 0;

    //Open the file of messages to be classified
    iFile.open(inputDataPath);
    if (!iFile.is_open()) {
        cout << "Error opening data to classify file\n";
        return 1;
    }

    string line;
    //ignore the first line headers
    getline(iFile, line);

    fstream oFile(outputPath, ios_base::out);
    if (!oFile.is_open()) {
        cout << "Error opening data to classify file\n";
        return 1;
    }
    //write headers to output file
    oFile << "v1,v2,,,\n";
    oFile.close();

    while (getline(iFile, line)) {
        //keep track of total message
        totalMessages++;
        //parsing variables
        stringstream ssLine(line);
        string classType;
        string data;
        //store string before cleaning to write to output file
        string originalMessage;

        //store class type (for checking accuracy) and the message data
        getline(ssLine, classType, ',');
        getline(ssLine, data);
        originalMessage = data;

        //clean data. Remove punctuation and make lower case
        data.erase(remove_if(data.begin(), data.end(), ::ispunct), data.end());
        transform(data.begin(), data.end(), data.begin(), ::tolower);

        //make stream of clean data for parsing
        stringstream ssData(data);
        string word;

        //probability of class to be multiplied by conditional probability of each word
        double probIsHam = probHamClass;
        double probIsSpam = probSpamClass;

        //Conditional probability of each word = (freq of word in class + 1)/ (total words in class + Number of unique words among both classes)
        while (true) {
            ssData >> word;
            double condProb;
            //calculate ham conditional probability
            auto it = hamMap.find(word);
            if (it != hamMap.end()) {
                condProb = ((it->second) + 1) / (totalHamWords + totalUniqueWords);
            } else {
                condProb = 1 / (totalHamWords + totalUniqueWords);
            }
            probIsHam *= condProb;


            //Calculate spam conditional probability
            it = spamMap.find(word);
            if (it != spamMap.end()) {
                condProb = ((it->second) + 1) / (totalSpamWords + totalUniqueWords);
            } else {
                condProb = 1 / (totalSpamWords + totalUniqueWords);
            }
            probIsSpam *= condProb;


            if (ssData.eof()) {
                break;
            }
        }
        //classify message based on which has the higher probability.
        string messageClass = (probIsHam >= probIsSpam) ? "ham" : "spam";
        oFile.open(outputPath, ios_base::app);
        if(!oFile.is_open()) {
            cout << "Error appending to output file\n";
            return 1;
        }
        oFile << messageClass << ',' << originalMessage << "\n";
        oFile.close();

        if (messageClass == classType) {
            numCorrectClasses++;
        }
        //cout << messageClass;


    }
    iFile.close();
    //Display accuracy
    double accuracy = (numCorrectClasses / totalMessages) * 100;
    cout << "Classification accuracy: " << fixed << setprecision(2) << accuracy << '%' << endl;



    return 0;

}