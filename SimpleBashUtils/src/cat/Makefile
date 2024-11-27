CC=gcc
CC_FLAGS=-c -Wall -Werror -Wextra -std=c11
LDFLAGS = 
BUILD_NAME = s21_cat

TEST_INPUT_DIR = test_inputs
TEST_OUTPUT_DIR = test_outputs
TEST_EXPECTED_DIR = test_expected


all: s21_cat test

s21_cat: s21_cat.o
	${CC} s21_cat.o ${LDFLAGS} -o ./${BUILD_NAME}

s21_cat.o: s21_cat.c
	${CC} ${CC_FLAGS} s21_cat.c -o s21_cat.o

test: prepare_test test_test leaks

test_test: cat_test.sh prepare_test
	./cat_test.sh test

prepare_test: cat_test.sh
	chmod +x cat_test.sh
	./cat_test.sh prepare_test

leaks: cat_test.sh
	./cat_test.sh leaks

rebuild: clean_all

clean: 
	rm -f ./*.o ./${BUILD_NAME}

clean_test:
	rm -rf $(TEST_INPUT_DIR) $(TEST_OUTPUT_DIR) $(TEST_EXPECTED_DIR)

clean_all: clean clean_test


