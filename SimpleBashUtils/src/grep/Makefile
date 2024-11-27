CC = gcc
CC_FLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS =
BUILD_NAME = s21_grep

TEST_INPUT_DIR = test_inputs
TEST_OUTPUT_DIR = test_outputs
TEST_EXPECTED_DIR = expected_outputs

all: s21_grep test

s21_grep: s21_grep.o
	${CC} s21_grep.o ${LDFLAGS} -o ./${BUILD_NAME}

s21_grep.o: s21_grep.c s21_grep.h
	${CC} ${CC_FLAGS} s21_grep.c -o s21_grep.o

test: prepare_test test_test leaks

test_test: grep_test.sh prepare_test
	./grep_test.sh test

prepare_test: grep_test.sh
	chmod +x grep_test.sh
	./grep_test.sh prepare_test

leaks: grep_test.sh
	./grep_test.sh leaks


clean:
	rm -f ./*.o ./${BUILD_NAME}

clean_test:
	rm -rf $(TEST_INPUT_DIR) $(TEST_OUTPUT_DIR) $(TEST_EXPECTED_DIR)

clean_all: clean clean_test

rebuild: clean_all
