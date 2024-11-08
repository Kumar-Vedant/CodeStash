#include <bits/stdc++.h>
#include "../include/branch.h"
#include "../include/repository.h"

using namespace std;

string getParentCommit(string commitHash)
{
    // get the content of the commit object (call catFile())

    // go to the second line and extract the parent hash
}

// find common ancestor
string findMergeBase(string b1, string b2)
{
    // get the commit objects for both branches
    string commit1 = refResolver("refs/heads/" + b1);
    string commit2 = refResolver("refs/heads/" + b2);

    // store all commits of the first branch
    unordered_set<string> visitedCommits;

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
}

// compare changes in two branches
void compareChanges(string b1, string b2)
{
    // find the merge base commit

    // get the tree objects for all 3 (branch 1, branch 2 and merge base)

    // recursively traverse each tree structure to get all file hashes

    // if two files have the same hash, they are identical (no problem)

    // if two files (one in merge base and the other in a branch) have the same name but different hashes, mark it as modified


    // check each modified file line by line using Myer's diff
}

// merge branches

// 