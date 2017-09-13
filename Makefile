
CXX = g++
CC = g++

CXXFLAGS = -Wall -Werror -Wpedantic -std=c++1z
LDFLAGS = 

.PHONY: clean all default

executables = test test2 test3

default: $(executables)

clean:
	rm -f $(executables)

all: clean default




