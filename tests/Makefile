ARGS := -Wall
INCLUDE := -I../include/
SRC := ../src/debug.cpp

all:
	g++ ${ARGS} ${INCLUDE} ${SRC} ../src/funcs.cpp ../src/ConfigFile.cpp test_runner.cpp -o test.out

test:
	g++ ${ARGS} ${INCLUDE} ${SRC} ../src/funcs.cpp ../src/ConfigFile.cpp test_runner.cpp -o test.out; ./test.out

clean:
	rm test.out

.PHONY: all test clean