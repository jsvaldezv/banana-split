#!/bin/bash

echo "=========================================="
echo "               Starting..."
echo "=========================================="

# ============================================================================

directory="BananaSplit/Source"

# Find all files in the directory and its subdirectories
file_list=$(find "$directory" -type f)

# Iterate over each file in the list
for file in $file_list; do
    echo "Formatting: $file"
	clang-format --style=file -i $file
done