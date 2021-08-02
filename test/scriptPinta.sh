#script usado para testar o despinta. Compara o grafo antes de pintar com o grafo depois de despintar
./script.sh > compara.txt
split -l 100 -d --additional-suffix=.txt compara.txt file
cmp --silent file00.txt file01.txt || echo "files are different"
# cat file01.txt