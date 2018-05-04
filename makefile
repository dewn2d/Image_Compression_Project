CC=gcc
CFLAGS=-I. 
DEPS = 	./Includes/encoder.h ./Includes/decoder.h ./Includes/inc_def.h
OBJ = 	Project.o encoder.o decoder.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Project: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) `pkg-config --libs --cflags opencv` -ldl -lm

clean :
	-rm *.o $(OBJ) 
