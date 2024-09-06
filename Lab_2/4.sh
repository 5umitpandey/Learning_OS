#!/bin/bash

read -p "Enter a character: " ch

case $ch in
    "a" | "e" | "i" | "o" | "u" | "A" | "E" | "I" | "O" | "U")
        echo "It is a vowel."
        ;;
    *)
        echo "It is a consonant."
        ;;
esac