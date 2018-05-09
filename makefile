CC=gcc
CFLAGS=-I"C:\OpenCV-3.4.0\opencv\build\include" 
DEPS = 	./Includes/encoder.h ./Includes/decoder.h ./Includes/inc_def.h
OBJ = 	Project.o encoder.o decoder.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Project: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm

clean :
	-rm *.o $(OBJ) 

	C:\WinAVR-20100110\bin