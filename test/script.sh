#!/bin/bash
./geramapa 10 10 2 > input.txt
./floodit_h1 < input.txt > output1.txt
./floodit_h2 < input.txt > output2.txt
./.././a.out < input.txt > output3.txt
clear
# cat input.txt output3.txt | ./anima

cat output1.txt
cat output2.txt
cat output3.txt
cat input.txt output1.txt | ./verifica
cat input.txt output2.txt | ./verifica
cat input.txt output3.txt | ./verifica

