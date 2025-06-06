# Git_like

## Project Overview

This project is an implementation of a basic version control system, inspired by Git, written in C++. The purpose of this project is to build a foundational understanding of how version control systems like Git work internally, including features like commits, branching, staging, and repository management.

## Key Features

- Repository Creation: Initialize a new repository in any directory.
- Staging Area (Index): Add and remove files to the staging area before committing changes.
- Commit System: Track snapshots of the staged changes.
- Branching: Create and manage branches for parallel development.
- Checkout: Switch between branches or revert to specific commits.
- Log: View the history of commits.
- Diff: Compare changes between different commits or the working directory and the latest commit.
- Reset: Unstage or undo changes in the repository.
- Merge: Combine two branches together.
- Conflict Resolution: Handle conflicts during merges.
- Interactive Staging: Stage specific lines or parts of a file.

## Usage

g++ src/cli.cpp src/merge.cpp src/staging.cpp src/commit.cpp src/branch.cpp src/repository.cpp -o gitlikeEVM -lssl -lcrypto -lz

## Project Structure

├── src # Source files\
│ ├── cli.cpp # Entry point for the program, handles command management\
│ ├── repository.cpp # Handles repository creation and management\
│ ├── commit.cpp # Manages commit creation and history\
│ └── branch.cpp # Handles branch creation and management\
├── include # Header files\
│ ├── repository.h # Declaration for repository management\
│ ├── commit.h # Declaration for commit-related functions\
│ └── branch.h # Declaration for branch management\
├── .gitlike/ # Data storage for the version control (generated on init)\
│ ├── objects/ # Stores commit objects\
│ ├── refs/ # Stores branch references\
│ └── HEAD # Points to the current branch/commit\
└── Makefile # build script
