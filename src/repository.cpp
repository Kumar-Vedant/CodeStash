#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "zstr.hpp"

using namespace std;

namespace fs = std::filesystem;

void initializeRepo(string path)
{
    // create correct paths for use
    fs::path worktree(path);
    fs::path file(".gitlike");

    fs::path gitdir = worktree/file;

    // create .gitlike subdirectory
    fs::create_directories(file);
    
    // create directories objects, refs, refs/heads and refs/tags
    fs::create_directories(file/"objects");
    fs::create_directories(file/"refs");
    fs::create_directories(file/"refs/heads");
    fs::create_directories(file/"refs/tags");

    // create and write stuff in HEAD file
    ofstream headFile(file/"HEAD");

    if(headFile.is_open())
    {
        headFile << "ref: refs/heads/main" << endl;
        headFile.close();
    }
    else
    {
        cerr << "Failed to create .gitlike/HEAD file" << endl;
    }

    // create and write stuff in config file


    cout << "git direc initialized" << endl;
}

void catFile(string shaHash)
{
    // calculate the path to the file
    string folder = shaHash.substr(0, 2);
    string file = shaHash.substr(2);

    fs::path path = ".gitlike/objects";
    path /= folder;
    path /= file;

    // read the file at the given path
    zstr::ifstream f(path, ofstream::binary);
    if (!f.is_open())
    {
        cerr << "invalid gitlike object!" << endl;
    }
    
    // decompress it's contents
    stringstream ss;
    ss << f.rdbuf();
    f.close();

    // remove headers
    string content = ss.str().substr(ss.str().find("\0") + 1);

    // print the contents
    cout << ss.str() << endl;
}
void hashObject(string path)
{
    // read the file
    zstr::ifstream f(path, ofstream::binary);

    // create a header
    string header = "";

    // convert the header and it's entire content into a SHA-1 hash


    // print the hash

    // separate the first two characters of the hash
    
    // create the file first-2-characters/rest

    // compress the contents of the file and write it to the new git object file
}

int main(int argc, char const *argv[])
{
    initializeRepo("./");
    return 0;
}