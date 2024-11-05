#include <bits/stdc++.h>

using namespace std;

namespace fs = std::filesystem;

// ref
string refResolver(string ref)
{
    // if the file doesn't exist, return
    // if(filesystem::exists())
    // {
    //     return;
    // }

    fs::path refPath(".gitlike/");
    refPath /= ref;

    // open the file at the path
    ifstream f(refPath);
    string data;
    {
        stringstream buffer;
        buffer << f.rdbuf();
        data = buffer.str();
    }
    f.close();

    // if it starts with "ref: ", call it recursively on the remaining part
    if(data.find("ref: ") == 0)
    {
        return refResolver(data.substr(5));
    }
    // return the SHA-1 hash
    else
    {
        return data;
    }
}

// lists all references in the repo
void showReferences()
{
    // traverse to the refs directory
    fs::path refsPath(".gitlike/refs");

    // put all refs in a set
    set<string> refs;

    // iterate through all files
    for (const auto & entry : fs::recursive_directory_iterator(refsPath))
    {
        // check if it's a regular file
        if (fs::is_regular_file(entry.path()))
        {
            // remove "./gitlike" and add the address to the set
            string filePath = entry.path().string();
            refs.insert(filePath.substr(9));
        }
    }

    // resolve all refs and print the results along with the address to the reference
    for(string i: refs)
    {
        cout << refResolver(i) << " " << i << endl;
    }
}

// tags
void createTag(string tag)
{
    // create a file with the given name in .gitlike/refs/tags/

    // get the hash of the current commit

    // write this hash into the file created
}

// branches

int main(int argc, char const *argv[])
{
    showReferences();
    return 0;
}