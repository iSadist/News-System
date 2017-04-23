#
# Makefile to make the file libclientserver.a, containing
# connection.o and server.o
#
# Define the compiler. g++ can be
# changed to clang++.
CXX = g++
CC  = g++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of libstdc++.
CPPFLAGS =  -std=c++11 -I./server
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += -std=c++11
CXXFLAGS += -g
#CXXFLAGS =  -stdlib=libc++
#CPPFLAGS =  -stdlib=libc++
#CXXFLAGS += -stdlib=libc++

all: clean libclientserver.a subpaths

# Create the library; ranlib is for Darwin (OS X) and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: connection.o server.o messagehandler.o
	ar rv libclientserver.a  connection.o server.o
	ranlib libclientserver.a

subpaths:
	cd ./client && make clean && make && mv client ../bin/client
	cd ./server && make clean && make && mv perfectserver ../bin/memoryserver
	cd ./server && make clean && make db=-DSQL && mv perfectserver ../bin/sqlserver

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -rf *.o libclientserver.a bin
	mkdir bin

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
