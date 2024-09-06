#!/bin/bash

read -p "Enter the number of terms: " n

a=0
b=1

echo "Fibonacci series up to $n terms:"


echo -n "$a, $b"

for (( i=2; i<n; i++ ))
do
    fn=$((a + b))
    echo -n ", $fn"
    
    a=$b
    b=$fn
done