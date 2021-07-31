#!/bin/bash
echo "testando...."
./geramapa 50 50 5 > input.txt
./floodit_h1 < input.txt > output.txt
cat input.txt > ../test.txt 
cat output.txt >> ../test.txt
cd ..
./a.out < test.txt