#!/bin/bash
./geramapa 5 5 3 > input.txt
./floodit_h1 < input.txt > output.txt
cat input.txt > ../test.txt 
cat output.txt >> ../test.txt
cd ..
./a.out < test.txt