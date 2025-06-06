#include <string>
#include <filesystem>
#include <fstream>
#include "iostream"
#include "../include/repository.h"

namespace fs = std::filesystem;

using namespace std;
// creating an index file to store the file paths and their hash values
void createIndex() {
    // create .gitlike/index if it doesn't exist
    fs::path indexPath = ".gitlike/index";
    if (!fs::exists(indexPath)) {
        ofstream indexFile(indexPath);
        if (!indexFile) {
            cerr << "Failed to create index file" << endl;
        }
        indexFile.close();
    }

}

void stageFile(string filePath) {
    // hash the file's contents
    string fileHash = hashObject(filePath);

    // open the index file to store the file path and its hash
    fs::path indexPath = ".gitlike/index";
    ofstream indexFile(indexPath, ios::app);

    if (indexFile.is_open()) {
        indexFile << filePath << " " << fileHash << endl;
        indexFile.close();
        cout << "File " << filePath << " staged successfully." << endl;
    } else {
        cerr << "Failed to update index." << endl;
    }
}

void showStagedFiles() {
    fs::path indexPath = ".gitlike/index";
    ifstream indexFile(indexPath);

    if (indexFile.is_open()) {
        string line;
        while (getline(indexFile, line)) {
            cout << line << endl;
        }
        indexFile.close();
    } else {
        cerr << "Index file not found." << endl;
    }
}

void clearStagingArea() {
    fs::path indexPath = ".gitlike/index";
    ofstream indexFile(indexPath, ios::trunc);  // truncate the index file
    indexFile.close();
    cout << "Staging area cleared." << endl;
}
