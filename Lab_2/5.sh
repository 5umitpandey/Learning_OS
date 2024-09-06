#!/usr/bin/bash
# Path to the file
file_path="/home/amninder/Desktop/demo.txt"

# Count the number of lines and words
number_of_lines=$(wc --lines < "/media/sf_Ubuntu_Files/1.sh")
number_of_words=$(wc --word < "/media/sf_Ubuntu_Files/3.sh")

# Display the results
echo "Number of lines: $number_of_lines"
echo "Number of words: $number_of_words"