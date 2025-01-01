#!/bin/sh

echo "Enter A"
read a
echo "Enter B"
read b
echo "Enter C"
read c
if [ "$a" -gt "$b"  -a  "$a" -gt "$c" ]; then
echo "A is largest" 
elif [ "$b" -gt "$a" -a "$b" -gt "$c" ]; then
echo "B is the largest" 
else
echo "C is the largest"
fi

