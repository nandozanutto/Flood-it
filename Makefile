CC=gcc
CFLAGS= 
DEPS = graph.h guloso.h painting.h 
OBJ = main.o graph.o guloso.o painting.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

floodIt: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "******Execute o arquivo floodIt" 

clean:
	rm -f *.o floodIt
