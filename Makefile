# glee makefile

STD=-std=c99
WFLAGS=-Wall -Wextra
OPT=-O2
IDIR=-I.
LIBS=-lglfw
CC=gcc
NAME=libglee
SRC=src/*.c

SCRIPT=build.sh

MAC=-framework OpenGL
LINUX=-lGL -lGLEW

CFLAGS=$(STD) $(WFLAGS) $(OPT) $(IDIR)

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	OSFLAGS=$(MAC) -dynamiclib
	LIB=$(NAME).dylib
else
	OSFLAGS=$(LINUX) -shared -fPIC
	LIB=$(NAME).so
endif

$(NAME).a: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) && ar -cr $(NAME).a *.o && rm *.o

shared: $(SRC)
	$(CC) -o $(LIB) $(SRC) $(CFLAGS) $(LIBS) $(OSFLAGS)

clean: $(SCRIPT)
	./$^ $@

install: $(SCRIPT)
	./$^ $@

uninstall: $(SCRIPT)
	./$^ $@

