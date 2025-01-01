#!/bin/sh

echo "program to perform KILL operations"
ps
echo enter the pid
read pid
kill-9 $pid
echo finished
