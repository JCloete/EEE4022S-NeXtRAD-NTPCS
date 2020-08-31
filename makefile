.RECIPEPREFIX +=
CC = gcc

PROG = bin/*
OBJS = build/*


default:
    mkdir -p bin build
    $(CC) -c src/main.c -o build/main.o
    $(CC) -o bin/main build/main.o

run:
    bin/main

clean: 
    rm -rf $(PROG) $(OBJS) 