# CodeStash

A local Version Control System (VCS) with core Git-like features: commits, branches, logs, and
merge conflict resolution along with efficient object storage using zlib compression and SHA-1 hashing, written in C++.

# Features

- Commit System: Track snapshots of the commited changes.
- Branching: Create and manage branches for parallel development.
- Checkout: Switch between branches or revert to specific commits.
- Log: View the history of commits.
- Merge: Combine two branches together.
- Diff: Compare changes between different commits or the working directory and the latest commit.
- Conflict Resolution: Handle conflicts during merges.

## Usage

```bash
git clone https://github.com/Kumar-Vedant/Version_Control_System.git
```

1. Download zstr from github.
2. Compile the files using: `bash g++ src/cli.cpp src/merge.cpp src/staging.cpp src/commit.cpp src/branch.cpp src/repository.cpp -o vcs -lssl -lcrypto -lz `
3. Copy the compiled file vcs into the directory you wish to track.
4. Open a terminal in the folder and run the file as such: `bash ./vcs init`
5. Check the whole list of supported commands available in src/cli.cpp

## Tech Stack

- C++
- File Compression: zstr, zlib
- Hashing: openSSL

## License

```
MIT License

Copyright (c) 2025 Kumar Vedant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
