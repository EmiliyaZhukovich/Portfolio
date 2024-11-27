#!/bin/bash

TEST_INPUT_DIR="test_inputs"
TEST_OUTPUT_DIR="test_outputs"
TEST_EXPECTED_DIR="test_expected"
BUILD_NAME="s21_cat"


prepare_test() {
    mkdir -p "$TEST_INPUT_DIR" "$TEST_OUTPUT_DIR" "$TEST_EXPECTED_DIR"
    echo -e "abc\n\t\n\x01\n\x02\n\x7F" > "$TEST_INPUT_DIR/test1.txt"
    echo -e "Line1\nLine\t\n\t\t\t\n\n\n\tLine3" > "$TEST_INPUT_DIR/test2.txt"
    echo -e "\n\n\n\n\nOnly empty lines\n\n\n\n\n\n" > "$TEST_INPUT_DIR/test3.txt"
    echo -e "Another file content for testing\nAnd more lines here\n" > "$TEST_INPUT_DIR/test4.txt"
}

run_tests() {
    echo "Running tests..."
    for file in "$TEST_INPUT_DIR"/*; do
        for flags in "-b" "--number-nonblank" "-n" "--number" "-s" "--squeeze-blank" "-E" "-e" "-T" "-t"; do
            output_file="$TEST_OUTPUT_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            expected_file="$TEST_EXPECTED_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            ./"$BUILD_NAME" $flags "$file" > "$output_file"
            cat $flags "$file" > "$expected_file"
            if diff -q "$output_file" "$expected_file" > /dev/null; then
                echo "PASS: $file $flags"
            else
                echo "FAIL: $file $flags"
                diff "$output_file" "$expected_file"
            fi
        done
    done

    echo "Running multi-file tests..."
    ./"$BUILD_NAME" -b "$TEST_INPUT_DIR/test1.txt" "$TEST_INPUT_DIR/test2.txt" > "$TEST_OUTPUT_DIR/multi_file_test_b"
    cat -b "$TEST_INPUT_DIR/test1.txt" "$TEST_INPUT_DIR/test2.txt" > "$TEST_EXPECTED_DIR/multi_file_test_b"
    if diff -q "$TEST_OUTPUT_DIR/multi_file_test_b" "$TEST_EXPECTED_DIR/multi_file_test_b" > /dev/null; then
        echo "PASS: multi_file_test_b with -b"
    else
        echo "FAIL: Multi-file test with -b"
        diff "$TEST_OUTPUT_DIR/multi_file_test_b" "$TEST_EXPECTED_DIR/multi_file_test_b"
    fi

    ./"$BUILD_NAME" -nE "$TEST_INPUT_DIR/test3.txt" > "$TEST_OUTPUT_DIR/multi_flag_test_n_E"
    cat -nE "$TEST_INPUT_DIR/test3.txt" > "$TEST_EXPECTED_DIR/multi_flag_test_n_E"
    if diff -q "$TEST_OUTPUT_DIR/multi_flag_test_n_E" "$TEST_EXPECTED_DIR/multi_flag_test_n_E" > /dev/null; then
        echo "PASS: multi_flag_test_n_E with -nE"
    else
        echo "FAIL: Multi-flag test with -nE"
        diff "$TEST_OUTPUT_DIR/multi_flag_test_n_E" "$TEST_EXPECTED_DIR/multi_flag_test_n_E"
    fi
    ./"$BUILD_NAME" -s -t "$TEST_INPUT_DIR/test1.txt" > "$TEST_OUTPUT_DIR/multi_flag_test_s_t"
    cat -s -t "$TEST_INPUT_DIR/test1.txt" > "$TEST_EXPECTED_DIR/multi_flag_test_s_t"
    if diff -q "$TEST_OUTPUT_DIR/multi_flag_test_s_t" "$TEST_EXPECTED_DIR/multi_flag_test_s_t" > /dev/null; then
        echo "PASS: multi_flag_test_s_t with -st"
    else
        echo "FAIL: Multi-flag test with -st"
        diff "$TEST_OUTPUT_DIR/multi_flag_test_s_t" "$TEST_EXPECTED_DIR/multi_flag_test_s_t"
    fi
}

check_leaks() {
    echo "Running memory leak checks with valgrind..."
    for file in "$TEST_INPUT_DIR"/*; do
        for flags in "-b" "--number-nonblank" "-n" "--number" "-s" "--squeeze-blank" "-E" "-e" "-T" "-t"; do
            echo "Testing $file $flags"
            valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./"$BUILD_NAME" $flags "$file" > /dev/null 2>&1 || exit 1
        done
    done
    echo "Memory leak checks passed!"
}

case $1 in
    prepare_test)
        prepare_test
        ;;
    test)
        prepare_test
        run_tests
        ;;
    leaks)
        prepare_test
        check_leaks
        ;;
    *)
        echo "Usage: $0 {prepare_test|test|leaks}"
        exit 1
        ;;
esac
