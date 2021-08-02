#!/bin/bash
./geramapa 10 10 2 > input.txt
./floodit_h1 < input.txt > output.txt
cat input.txt > ../test.txt 
cat output.txt >> ../test.txt
cd ..
./a.out < test.txt