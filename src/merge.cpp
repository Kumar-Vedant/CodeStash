#include <bits/stdc++.h>
#include "../include/branch.h"
#include "../include/repository.h"

namespace fs = std::filesystem;

using namespace std;

string getParentCommit(string commitHash)
{
    // cout << commitHash;
    // get the content of the commit object (call catFile())
    string commitContent = catFile(commitHash);

    // go to the second line and extract the parent hash
    
    // extract the second line
    int secondLineStart = commitContent.find('\n') + 1;
    int secondLineEnd = commitContent.find('\n', secondLineStart);
    commitContent = commitContent.substr(secondLineStart, secondLineEnd-secondLineStart - 1);

    // cout << commitContent << endl;

    // remove the "parent " text
    string parentHash = commitContent.substr(7);

    return parentHash;
}

// find common ancestor
string findMergeBase(string b1, string b2)
{
    // get the commit objects for both branches
    string commit1 = refResolver("refs/heads/" + b1);
    string commit2 = refResolver("refs/heads/" + b2);

    cout << commit1 << endl;
    cout << commit2;
    // store all commits of the first branch
    set<string> visitedCommits;

    // traverse the commit history of branch 1
    while(commit1 != "0")
    {
        // store the commit hash
        visitedCommits.insert(commit1);
        // move a step earlier in the commit history
        commit1 = getParentCommit(commit1);
    }

    // traverse the commit history of branch 2 and find the first common commit
    while(commit2 != "0")
    {
        // if the commit is in the visited set, return it
        if(visitedCommits.find(commit2) != visitedCommits.end())
        {
            return commit2;
        }
        // move a step earlier in the commit history
        commit2 = getParentCommit(commit2);
    }
    return " ";
}

set<string> traverseTree(string treehash)
{
    set<string> treeItems;

    // get the tree's content
    string treeContent = catFile(treehash);

    // parse each line
    istringstream stream(treeContent);
    string line;

    // read each line from the stream
    while (getline(stream, line))
    {
        // if file, store the entire content
        if(line.find("100644") == 0)
        {
            treeItems.insert(line);
        }

        // if it is another tree object, recursively parse the tree object
        if(line.find("040000") == 0)
        {
            // get the hash of the object
            string hash = line.substr(line.find('\0') + 1);
            
            // traverse recursively and combine the vectors
            set<string> subDirItems = traverseTree(hash);
            treeItems.insert(subDirItems.begin(), subDirItems.end());
        }
    }
    return treeItems;
}

// compare changes in two branches
string compareChanges(string b1, string b2)
{
    // find the merge base commit
    // string mergeBase = findMergeBase(b1, b2);

    // recursively traverse each tree structure to get all file hashes
    set<string> files1 = traverseTree(b1);
    set<string> files2 = traverseTree(b2);

    set<string> finalFiles;
    set<string> modifiedFiles;

    // iterate through files1
    for(string i: files1)
    {
        // if two files have the same hash, they are identical (no problem)
        if(files2.find(i) != files2.end())
        {
            finalFiles.insert(i);
            files2.erase(i);
            continue;
        }

        string f1 = i.substr(i.find(" "), i.find(" ")-i.find('\0')-1);

        bool isModified = false;
        for(string j: files2)
        {
            string f2 = j.substr(j.find(" "), j.find(" ")-j.find('\0')-1);

            // if two files have the same paths but different hashes, mark it as modified
            if(f1 == f2)
            {
                isModified = true;
                modifiedFiles.insert(i);
                modifiedFiles.insert(j);
                files2.erase(j);
                break;
            }
        }       
        // if one file exists in a branch but not in the other, include it
        if(!isModified)
        {
            finalFiles.insert(i);
        }
    }

    // put all files only left in files2
    for(string i: files2)
    {
        finalFiles.insert(i);
    }

    // iterate to find all modified files
    for(string f: modifiedFiles)
    {
        modifiedFiles.erase(f);
        string filePath1 = f.substr(f.find(" "), f.find(" ")-f.find('\0')-1);

        for(string g: modifiedFiles)
        {
            string filePath2 = g.substr(g.find(" "), g.find(" ")-g.find('\0')-1);

            if(filePath1 == filePath2)
            {
                // get the file content of both files (call catFile())
                string hash1 = f.substr(f.find('\0'));
                string hash2 = g.substr(g.find('\0'));

                string content1 = catFile(hash1);
                string content2 = catFile(hash2);

                // check each modified file line by line using Myer's diff

                // combine the code that is common

                // for the code different, mark it using <<< >>>

                // put both of them in a text file and open it in a text editor
                ofstream conflictFile(filePath1.substr(filePath1.find_last_of("/")));

                conflictFile << content1;
                conflictFile << endl;
                conflictFile << "---------------------------------" << endl;
                conflictFile << endl;
                conflictFile << content2;

                // open nano text editor to update changes
                string command = "nano " + filePath1.substr(filePath1.find_last_of("/"));

                // execute the command
                system(command.c_str());
                conflictFile.close();

                string blobHash = hashObject(filePath1);

                finalFiles.insert("100644 " + filePath1 + '\0' + blobHash + '\n');
                break;
            }
        }
    }

    string treeContent;
    // create a new tree object
    for(string i: finalFiles)
    {
        treeContent += i;
    }

    string header = "tree " + to_string(treeContent.size()) + '\0';
    string treeData = header + treeContent;

    cout << treeData;
    // create a file to store the records
    ofstream f("treeObjDummy.txt");
    
    // store all the records in a file
    f << treeData;
    f.close();

    // create a tree git-object for it (call hashObject())
    string treeHash = hashObject("treeObjDummy.txt");

    // delete the original file
    fs::remove("treeObjDummy.txt");

    string commitContent;

    commitContent += "tree " + treeHash + "\n";
    commitContent += "parent " + b1 + " " + b2 + "\n";

    // create a file to store the records
    ofstream file("commitObjDummy.txt");
    
    // store all the records in a file
    file << commitContent;
    file.close();

    // create a commit git-object for it (call hashObject())
    string commitHash = hashObject("commitObjDummy.txt");

    // delete the original file
    fs::remove("commitObjDummy.txt");

    return commitHash;
}

// merge branches
void mergeBranch(string branch)
{
    // combine the given branch with the current branch and get a tree object for the new commit
    ifstream mainBranch("./.gitlike/HEAD");
    string data;

    stringstream buffer;
    buffer << mainBranch.rdbuf();
    data = buffer.str();

    mainBranch.close();
    data = data.substr(5);
    // cout << data;

    // remove "ref: " and get the commit hash of both branches
    string currentBranchHash = refResolver(data);
    string mergeBranchHash = refResolver("refs/heads/" + branch);

    // create a new commit object with 2 parent branches
    string commitHash = compareChanges(currentBranchHash, mergeBranchHash);

    // move both the branches to the new commit
    ofstream b1("./.gitlike/refs/heads/" + branch);
    // if(b1.is_open()) {cout << "h1";}
    b1 << commitHash;
    b1.close();

    ofstream b2("./.gitlike/" + data);
    // if(b2.is_open()) {cout << "h2";}
    b2 << commitHash;
    b2.close();
}