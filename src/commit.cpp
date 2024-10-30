#include <string>

using namespace std;

void createCommit(string commitMessage)
{
    // find the working directory

    // get a list of all the modified files from the staging area

    // for each modified file, compute the SHA-1 hash (call hashObject())

    // update the index file?

    // create a tree object representing the working directory

    // write commit metadata (tree hash, parent, author, committer, timestamp, message)

    // create a commit git-object for the new commit (call hashObject()) and store it in .gitlike/objects
}

void log()
{
    // find the .gitlike directory

    // get the reference to the HEAD ref, which contains the reference to the latest commit

    // each commit has a parent reference
    // print the contents of the current commit (including author, committer, timestamp, message)
    // recursively call the log function on the parent commit
}

void createTreeObject(string path)
{
    // traverse the directory

    // for each file, read the file

    // retrieve the file mode, it's path and compute it's SHA-1 hash
    // make a record to store in the tree object in the format: [mode] space [path] 0x00 [sha-1]

    // for a folder, call this function recursively

    // store all the records in a file
    // create a tree git-object for it (call hashObject())
    // delete the file

    // return own's hash received by hashObject()
}

// function to restore a directory to a commit
// it can take a commit hash or a branch name
void checkout(string commitHash)
{
    // check if branch name OR commit hash

    // get the commit git-object from the object database

    // retrieve the tree object hash from the commit object

    // get the uncompressed content of the tree git-object (call catFile())


    // recreate directory structure

    // parse the content line by line

    // if it is a blob, create a file in the working directory
    // get the uncompressed content of the blob file (call catFile())
    // put the contents into the new file created

    // if it is another tree object, create a directory and recursively parse the tree object

    // update index (staging area)
    // update the HEAD reference
}