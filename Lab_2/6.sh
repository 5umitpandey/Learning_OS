#!/bin/bash
# Accept the file name as a command line argument
file="/media/sf_Ubuntu_Files/5.sh"

# Check if the file exists
if [ ! -e "$file" ]; then
    echo "File '$file' does not exist."
    exit 1
fi

# Display file information
echo "File: $file"
echo "Size: $(du -h "$file" | awk '{print $1}')"
echo "Permissions: $(stat -c '%A' "$file")"
echo "Owner: $(stat -c '%U' "$file")"
echo "Modification time: $(stat -c '%y' "$file")"