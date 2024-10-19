#include "../include/branch.h"
#include "../include/commit.h"
#include "../include/repository.h"

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
        
    }
    return 0;
}
