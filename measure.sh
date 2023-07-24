#!/bin/bash

# Check if the number of arguments is 2
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file1> <file2>"
    exit 1
fi

# Check if the arguments are files
if [ ! -f $1 ]; then
    echo "$1 is not a file"
    exit 1
fi

if [ ! -f $2 ]; then
    echo "$2 is not a file"
    exit 1
fi

# Get the size of the files
size1=$(wc -c < $1)
size2=$(wc -c < $2)

# Calculate the compression ratio
ratio=$(awk "BEGIN {printf \"%.6f\", $size2 / $size1}")

# Print the result
echo "$1 is $size1 bytes"
echo "$2 is $size2 bytes"
echo "Data compression ratio: $ratio"
