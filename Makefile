INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
# If you are compiling this to run on CISC210,
# uncomment the below line
# LDFLAGS := $(LDFLAGS) -lncurses

all: snake

snake: main.o display.o input.o
	cc -o snake input.o main.o display.o $(LDFLAGS)

emu: main.o display.o input.o
	cc -o snake input.o main.o display.o $(LDFLAGS) -lncurses

run:
	./snake

clean:
	rm -f *.o snake

main.o: main.c snake.h
	cc -c main.c $(INCLUDE)

display.o: display.c snake.h
	cc -c display.c $(INCLUDE)

input.o: input.c snake.h
	cc -c input.c $(INCLUDE)
