#!/bin/bash

read -p "Enter the first string: " str1

read -p "Enter the second string: " str2

if [ "$str1" = "$str2" ]; then
    echo "The strings are equal."
else
    echo "The strings are not equal."
fi