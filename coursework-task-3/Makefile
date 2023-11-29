CC = gcc
CFLAGS = -Wall

LIBRARY = library.a
EXECUTABLE = calculator

all: $(LIBRARY) $(EXECUTABLE)

$(LIBRARY): calculator.o
	ar rcs $@ $^

$(EXECUTABLE): main.o $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(LIBRARY) $(EXECUTABLE)
