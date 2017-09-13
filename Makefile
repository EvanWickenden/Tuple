
CXX = g++
CC = g++

CXXFLAGS = -Wall -Werror -Wpedantic -std=c++1z
LDFLAGS = 

.PHONY: clean all default

executables = test test2 test3
objects = test.o test2.o test3.o

headers = list.hpp type.hpp tuple.hpp if.hpp

default: $(executables)

clean:
	rm -f $(executables) $(objects)

all: clean default


