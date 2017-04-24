# News-System
A project in C++ in a course at Lund University

To run build this you have to have SQLite3 installed.
Linux: sudo apt-get install sqlite3 libsqlite3-dev
Mac: brew install sqlite3

#Introduction

#Binary Deliverables

The delivery described in this report consists of three programs and their generation tools:
client
memoryserver
sqlserver

#Pre-requirements

This software has been developed and tested with g++ in both Ubuntu 16.04 and Apple OSX environments.

Additionally, it requires SQLite3 to be installed for the compilation and running of a server with a database that persists locally between several server program executions.

#Installing SQLite3:

On Linux: sudo apt-get install sqlite3 libsqlite3-dev
On Mac: brew install sqlite3

#Set-up

The delivery structure consists of the parentfolder which contains 2 folders (src / bin) and the master Makefile. Inside src there are the shared resources as well as a client and a server folder which contain the respective source files.

The Makefile inside the parent folder build the whole project when invoking make all in terminal from this directory. The build automation will thereafter populate the bin folder with the three binary deliverables aswell as the sqlite3 Database.db file which sqlserver uses as a local database.

Instruction list, assuming SQLlite3 is installed on the host pc:

Change directory to parent folder
Build project from parent folder: make all
Copy binaries to bin folder: make install
Change directory to bin and execute the binary of choice: ./[binaryname] 
Usage

All the programs are self-explanatory and contain usefull error messages, no documentation required.
