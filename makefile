CC = g++

CFLAGS = 

LIBS = Base.h Cars.h Packages.h

OBJECTS = Base.o Cars.o Packages.o main.o


OUTPUT = TEST

%.o: %.c $(LIBS)
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clear:
	rm -f *.o TEST