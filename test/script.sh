#!/bin/bash
./geramapa 100 100 20 > input.txt
./floodit_h1 < input.txt > output.txt
cat input.txt > ../test.txt 
cat output.txt >> ../test.txt
cd ..
./a.out < test.txt