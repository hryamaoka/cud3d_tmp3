#!/bin/bash

VALID_DIR="./assets/maps/valid"
INVALID_DIR="./assets/maps/invalid"
EXECUTABLE="./cub3D"
TIMEOUT_DURATION="1s"
LOG_FILE="verification_log.txt"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

> "$LOG_FILE"

pass_count=0
fail_count=0

echo "Starting verification..." | tee -a "$LOG_FILE"

# Function to check result
check_result() {
    local map_file=$1
    local expected_type=$2 # "valid" or "invalid"
    local exit_code=$3
    local output=$4

    local result="FAIL"
    local note=""

    if [ "$expected_type" == "invalid" ]; then
        # Fail if it timed out (meaning it kept running = passed validation)
        # OR if it exited with 0 (success)
        if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ]; then
            result="PASS"
            note="Exited with error as expected ($exit_code)"
        elif [ $exit_code -eq 124 ]; then
            result="FAIL"
            note="Timed out (Game started despite invalid map)"
        else
            result="FAIL"
            note="Exited with success (code 0) for invalid map"
        fi
    else # valid
        # Pass if timed out (kept running)
        # OR if it failed ONLY due to window initialization
        if [ $exit_code -eq 124 ]; then
            result="PASS"
            note="Timed out (Game started as expected)"
        elif echo "$output" | grep -q "Could not initialize window"; then
             result="PASS"
             note="Parsed OK, failed at window init (expected in headless)"
        elif echo "$output" | grep -q "mlx_init failed"; then
             result="PASS"
             note="Parsed OK, mlx_init failed (expected in headless)"
        elif echo "$output" | grep -q "Error: mlx failed"; then
             result="PASS"
             note="Parsed OK, mlx failed (Checking specific error msg might be needed)" 
        else
             result="FAIL"
             note="Exited with error: $output"
        fi
    fi

    if [ "$result" == "PASS" ]; then
        echo -e "${GREEN}[PASS]${NC} $map_file : $note" | tee -a "$LOG_FILE"
        pass_count=$((pass_count + 1))
    else
        echo -e "${RED}[FAIL]${NC} $map_file : $note" | tee -a "$LOG_FILE"
        fail_count=$((fail_count + 1))
    fi
}

echo "=== Testing Invalid Maps ===" | tee -a "$LOG_FILE"
for map in "$INVALID_DIR"/*.cub; do
    [ -e "$map" ] || continue
    out=$(timeout "$TIMEOUT_DURATION" "$EXECUTABLE" "$map" 2>&1)
    ret=$?
    check_result "$map" "invalid" $ret "$out"
done

echo "=== Testing Valid Maps ===" | tee -a "$LOG_FILE"
for map in "$VALID_DIR"/*.cub; do
    [ -e "$map" ] || continue
    out=$(timeout "$TIMEOUT_DURATION" "$EXECUTABLE" "$map" 2>&1)
    ret=$?
    check_result "$map" "valid" $ret "$out"
done

echo "========================================" | tee -a "$LOG_FILE"
echo "Total Tests: $((pass_count + fail_count))" | tee -a "$LOG_FILE"
echo -e "${GREEN}Passed: $pass_count${NC}" | tee -a "$LOG_FILE"
if [ $fail_count -gt 0 ]; then
    echo -e "${RED}Failed: $fail_count${NC}" | tee -a "$LOG_FILE"
else
    echo -e "${GREEN}Failed: 0${NC}" | tee -a "$LOG_FILE"
fi
