CC = g++
LIB = lib
INCLUDE = include
CFLAGS = -lraylib -lwinmm -lGdi32
OUT = bin/sensex

$(OUT): main.o
	$(CC) main.o -L$(LIB) $(CFLAGS) -o $(OUT)

main.o: src/main.cpp
	$(CC) src/main.cpp -c -I$(INCLUDE)

clean:
	rm *.o