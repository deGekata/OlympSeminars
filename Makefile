CWD := $(subst /,\, $(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))

all:
	g++ $(CWD)\3_sem\Base\Contest2\H-junctions.cpp -std=c++20 -o a.exe -O0 -g

run:
	a.exe