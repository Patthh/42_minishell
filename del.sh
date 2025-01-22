#!/bin/bash

# Check if a directory is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

DIRECTORY=$1

# Check if the directory exists
if [ ! -d "$DIRECTORY" ]; then
    echo "Error: Directory $DIRECTORY does not exist."
    exit 1
fi

# Iterate over all files in the directory
for FILE in "$DIRECTORY"/*; do
    if [ -f "$FILE" ]; then
        # Create a temporary file without the first 12 lines
        tail -n +13 "$FILE" > "${FILE}.tmp"
        
        # Replace the original file with the temporary file
        mv "${FILE}.tmp" "$FILE"
        echo "Processed: $FILE"
    fi
done

echo "All files in $DIRECTORY processed."

