#!/bin/bash
clear
rm ./a.out
gcc main.c
clear
echo "Input file name"
read inputfile
./a.out < $inputfile > intermediate
rm ./a.out
gcc ass.c
./a.out > finaloutput.asm
gedit finaloutput

