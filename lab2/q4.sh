#!/bin/sh

x=0
y=1

echo "$x"
echo "$y"
while [ "$x" -lt 10 ]; do
    z=$((x + y))
    if [ "$z" -gt 10 ]; then 
       break 
    fi
    echo "$z"
    x=$y
    y=$z
done
