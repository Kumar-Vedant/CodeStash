#include "../include/branch.h"
#include "../include/commit.h"
#include "../include/repository.h"
#include "../include/merge.h"
#include "../include/staging.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cerr << "No command provided" << endl;
    }

    string command = argv[1];

    // check the command given
    if(command=="init")
    {
        initializeRepo();
      
    }
    else if(command=="commit"){
        if(argc < 3)
        {
            cerr << "No message provided" << endl;
        }
        string message = argv[2];
        createCommit(message);
    }
    else if(command=="catFile")
    {
        if(argc < 3)
        {
            cerr << "No shaHash provided" << endl;
        }
        string shaHash = argv[2];
        cout << catFile(shaHash) << endl;
    }
    else if(command=="hashObject")
    {
        if(argc < 3)
        {
            cerr << "No path provided" << endl;
        }
        string path = argv[2];
        cout << hashObject(path) << endl;
    }
    else if(command=="checkout"){
        if(argc < 3)
        {
            cerr << "No ref provided" << endl;
        }
        string ref = argv[2];
        checkout(ref);
    }
    else if(command=="log"){
        log();
    }
    else if(command=="status"){
        // status();
    }
    else if(command=="branch"){
        if(argc < 3)
        {
            cerr << "No branch name provided" << endl;
        }
        string branchName = argv[2];
        createBranch(branchName);
    }
    else if(command=="showrefs"){
        showReferences();
    }
    else if(command=="lsBranches"){
        listBranches();
        
    }
    else if(command=="merge"){
        if(argc < 3)
        {
            cerr << "No branch name provided" << endl;
        }
        string branchName = argv[2];
        mergeBranch(branchName);
    }
    else if(command=="add"){
        if(argc < 3)
        {
            cerr << "No file path provided" << endl;
        }
        string filePath = argv[2];
        createIndex();
        stageFile(filePath);
    }
    else if(command=="showStagedFiles"){
        showStagedFiles();
    }
    else if(command=="reset"){
        clearStagingArea();
    }
    else
    {
        cerr << "Command not found" << endl;
    }
    return 0;
}