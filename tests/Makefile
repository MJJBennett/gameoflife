ARGS := -Wall
INCLUDE := -I../include/

all:
	g++ ${ARGS} ${INCLUDE} ../src/funcs.cpp test_runner.cpp -o test.out

test:
	g++ ${ARGS} ${INCLUDE} ../src/funcs.cpp test_runner.cpp -o test.out; ./test.out

clean:
	rm test.out

.PHONY: all test clean