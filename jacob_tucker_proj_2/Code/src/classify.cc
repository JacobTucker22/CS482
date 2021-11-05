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
        cout << "Correct Usage: ./classify -i <input file.csv> -is <spam input file.csv> -ih <ham input file.csv> -o <class output file.csv>\n"
                "Order of arguments does not matter as long as correct flags are in front of file paths\n";
        return 1;
    }


    return 0;

}