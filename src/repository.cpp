#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include "../zstr/zstr.hpp"

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

string catFile(string shaHash)
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

    return ss.str();
}

// function to create a git-object (blob, commit, tree, tag)

// create 4 implementations for each type
string hashObject(string path)
{
    // read the file
    zstr::ifstream f(path, ofstream::binary);

    // create a header
    string header = "";



    // convert the header and it's entire content into a SHA-1 hash



    // initialize a new message context
    EVP_MD_CTX* hashctx = EVP_MD_CTX_new();

    // set the context to use SHA-1
    EVP_DigestInit_ex(hashctx, EVP_sha1(), NULL);

    // Read the file in chunks and update the hash
    char buffer[8192];

    // read the file in chunks and update the hash context
    while (f.read(buffer, sizeof(buffer)) || f.gcount() > 0)
    {
        EVP_DigestUpdate(hashctx, buffer, f.gcount());
    }
    
    // finalize the hash
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    
    EVP_DigestFinal_ex(hashctx, hash, &lengthOfHash);

    // free the context
    EVP_MD_CTX_free(hashctx);

    // convert the hash into hexadecimal format
    stringstream ss;
    for (int i = 0; i < lengthOfHash; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    // print the hash
    // cout << ss.str() << endl;

    // separate the first two characters of the hash
    // calculate the path to the file
    string folder = ss.str().substr(0, 2);
    string file = ss.str().substr(2);

    fs::path filePath = ".gitlike/objects";
    filePath /= folder;
    fs::create_directories(filePath);

    filePath /= file;

    // compress the contents of the file and write it to the new git object file
    // open the file
    ifstream src(path, ofstream::binary);

    // open the git-object file created
    zstr::ofstream dst(filePath);

    // copy the compressed data from the source file to the git object file
    dst << src.rdbuf();

    return ss.str();
}

// int main(int argc, char const *argv[])
// {
//     // hashObject("./README.md");
//     initializeRepo("./");
//     return 0;
// }