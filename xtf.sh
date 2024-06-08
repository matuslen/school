#!/bin/bash

: "${XTF_PROFIT:=20}"

if [[ ! "$XTF_PROFIT" =~ ^[0-9]+$ ]] || [[ "$XTF_PROFIT" =~ ^- ]]; then
    echo "Invalid value for XTF_PROFIT environment variable."
    exit 1
fi

# Function to display help
display_help() {
    echo "Usage: xtf [-h|--help] [FILTR] [PŘÍKAZ] UŽIVATEL LOG [LOG2 [...]]"
    echo "Options:"
    echo "  PŘÍKAZ:"
    echo "    list - List records for the specified user."
    echo "    list-currency - List sorted list of currencies."
    echo "    status - Display account status grouped and sorted by currency."
    echo "    profit - Display customer account status with fictitious profit."
    echo "  FILTR:"
    echo "    -a DATETIME - Consider only records after this date and time (exclusive). Format: YYYY-MM-DD HH:MM:SS."
    echo "    -b DATETIME - Consider only records before this date and time (exclusive). Format: YYYY-MM-DD HH:MM:SS."
    echo "    -c CURRENCY - Consider only records corresponding to the given currency."
    echo "  -h, --help - Display this help message."
}

# Function to list records for the specified user
list_records() {
    local user="$1"
    local log_files=("${@:2}")

    for log_file in "${log_files[@]}"; do
        if [ -f "$log_file" ]; then
            echo "Records from $log_file for user $user:"
            grep "^$user" "$log_file"
        else
            echo "Warning: Log file '$log_file' not found."
        fi
    done
}

list_currency() {
    local user="$1"
    shift
    local log_files=("$@")
    for log_file in "${log_files[@]}"; do
        awk -v user="$user" -F';' '$1 == user && $3 != "" { currencies[$3] } END { for (currency in currencies) print currency }' "$log_files"
    done
}


status_function() {
    local user="$1"
    shift
    local log_files=("$@")
    for log_file in "${log_files[@]}"; do
      awk -v user="$user" -F';' '$1 == user && $3 != "" { sums[$3] += $4 } END { for (currency in sums) print currency " : " sums[currency] }' "$log_files"
    done
}


profit_function() {
    local user="$1"
    shift
    local log_files=("$@")
    profit_multiplier=$((100 + XTF_PROFIT))
    awk -v user="$user" -v profit_multiplier="$profit_multiplier" -F';' '$1 == user && $3 != "" {
    if ($4 >= 0) {
        $4 *= profit_multiplier / 100
    }
    sums[$3] += $4
} END { for (currency in sums) print currency " : " sums[currency] }' "$log_files"
}


# Default command
command="list"
filters=()

# Parse options
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            display_help
            exit 0
            ;;
        list|list-currency|status|profit)
            command="$1"
            shift
            ;;
        -a|-b|-c)
            if [[ $# -ge 2 ]]; then
                filters+=("$1 $2")
                shift 2
            else
                echo "Error: Argument missing for $1" >&2
                exit 1
            fi
            ;;
        *)
            break
            ;;
    esac
done

# Additional positional parameters
user="$1"
log_files="${@:2}"

# Perform actions based on the command
case $command in
    list)
        list_records "$user" "${log_files[@]}"
        ;;
    list-currency)
        list_currency "$user" "${log_files[@]}"
        ;;
    status)
        status_function "$user" "${log_files[@]}"
        ;;
    profit)
        profit_function "$user" "${log_files[@]}"
        ;;
    *)
        echo "Error: Invalid command '$command'" >&2
        exit 1
        ;;
esac

echo "Command: $command"
echo "Filters: ${filters[@]}"
echo "User: $user"
echo "Log files: $log_files"

for filter in "${filters[@]}"; do
    # Extract filter value
    read -r flag value <<< "$filter"
    
    # Run awk command to compare filter value with the third field of the log file
    awk -F';' -v user="$user" -v filter_value="$value" '$1 == user && $3 == filter_value { print "Name:", $1, "\nDate/Time:", $2, "\nCurrency:", $3, "\nAmount:", $4 }' "$log_files"
done

