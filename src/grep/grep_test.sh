#!/bin/bash

TEST_INPUT_DIR="test_inputs"
TEST_OUTPUT_DIR="test_outputs"
TEST_EXPECTED_DIR="expected_outputs"
BUILD_NAME="s21_grep"

prepare_test() {
    mkdir -p "$TEST_INPUT_DIR" "$TEST_OUTPUT_DIR" "$TEST_EXPECTED_DIR"
    echo -e "Hello world\ngrep example\nAnother line\n" > "$TEST_INPUT_DIR/patterns.txt" 
    echo -n "" > "$TEST_INPUT_DIR/empty.txt"  
    yes "This is a very long line for testing purposes" | head -n 10000 > "$TEST_INPUT_DIR/long.txt"
    echo -e "abc123\ndef456\nabc789\ndef123\n" > "$TEST_INPUT_DIR/regex_test.txt"
    echo -e "Hello\nworld\ngrep" > "$TEST_INPUT_DIR/patterns_file.txt"
}

run_tests() {
    echo "Running tests..."

    for file in "$TEST_INPUT_DIR"/*; do
        for flags in "-e world" "-i Hello" "-v grep" "-c Another" "-l Hello" "-n grep" "-h world" "-o line"; do
            output_file="$TEST_OUTPUT_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            expected_file="$TEST_EXPECTED_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            ./"$BUILD_NAME" $flags "$file" > "$output_file" 2>/dev/null
            grep $flags "$file" > "$expected_file" 2>/dev/null
            if diff -qZ "$output_file" "$expected_file" > /dev/null; then
                echo "PASS: $file $flags"
            else
                echo "FAIL: $file $flags"
                echo "Expected output:"
                cat "$expected_file"
                echo "Actual output:"
                cat "$output_file"
            fi
        done
    done

    echo "Running paired flags tests..."
    for file in "$TEST_INPUT_DIR"/*; do
        for flags in "-iv Hello" "-inl grep" "-cn world" "-lv Hello" "-ih world" "-on line"; do
            output_file="$TEST_OUTPUT_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            expected_file="$TEST_EXPECTED_DIR/$(basename "$file")_$(echo "$flags" | tr ' ' '_')"
            ./"$BUILD_NAME" $flags "$file" > "$output_file" 2>/dev/null
            grep $flags "$file" > "$expected_file" 2>/dev/null
            if diff -qZ "$output_file" "$expected_file" > /dev/null; then
                echo "PASS: $file $flags"
            else
                echo "FAIL: $file $flags"
                echo "Expected output:"
                cat "$expected_file"
                echo "Actual output:"
                cat "$output_file"
            fi
        done
    done

    echo "Running -f flag test..."
    ./"$BUILD_NAME" -f "$TEST_INPUT_DIR/patterns_file.txt" "$TEST_INPUT_DIR/patterns.txt" > "$TEST_OUTPUT_DIR/patterns_file_result" 2>/dev/null
    grep -f "$TEST_INPUT_DIR/patterns_file.txt" "$TEST_INPUT_DIR/patterns.txt" > "$TEST_EXPECTED_DIR/patterns_file_result" 2>/dev/null
    if diff -qZ "$TEST_OUTPUT_DIR/patterns_file_result" "$TEST_EXPECTED_DIR/patterns_file_result" > /dev/null; then
        echo "PASS: -f flag test"
    else
        echo "FAIL: -f flag test"
        echo "Expected output:"
        cat "$TEST_EXPECTED_DIR/patterns_file_result"
        echo "Actual output:"
        cat "$TEST_OUTPUT_DIR/patterns_file_result"
    fi

    echo "Running -s flag test..."
    output_file="$TEST_OUTPUT_DIR/nonexistent_file_s_flag"
    expected_file="$TEST_EXPECTED_DIR/nonexistent_file_s_flag"
    ./"$BUILD_NAME" -s -e "world" nonexistent_file.txt > "$output_file" 2>/dev/null
    grep -s -e "world" nonexistent_file.txt > "$expected_file" 2>/dev/null
    if diff -qZ "$output_file" "$expected_file" > /dev/null; then
        echo "PASS: -s flag test with nonexistent file"
    else
        echo "FAIL: -s flag test with nonexistent file"
        echo "Expected output:"
        cat "$expected_file"
        echo "Actual output:"
        cat "$output_file"
    fi
}

check_leaks() {
    echo "Running memory leak checks with valgrind..."
    for file in "$TEST_INPUT_DIR"/long.txt; do
        for flags in "-e world" "-i Hello" "-v grep" "-c Another" "-l Hello" "-n grep" "-h world" "-o line"; do
            echo "Checking leaks for $file $flags"
            valgrind --leak-check=full --show-leak-kinds=all ./"$BUILD_NAME" $flags "$file" > /dev/null 2>&1 || exit 1
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
