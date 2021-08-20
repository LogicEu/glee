# glee makefile

STD=-std=c99
WFLAGS=-Wall -Wextra
OPT=-O2
IDIR=-I.
LIBS=-lglfw
CC=gcc
NAME=libglee
SRC=src/*.c

MAC_LIBS=-framework OpenGL
LINUX_LIBS=-lGL -lGLEW

CFLAGS=$(STD) $(WFLAGS) $(OPT) $(IDIR)
OS=$(shell uname -s)

ifeq ($(OS),Darwin)
	OSFLAGS=$(MAC_LIBS) -dynamiclib
	LIB=$(NAME).dylib
else
	OSFLAGS=$(LINUX_LIBS) -shared -fPIC
	LIB=$(NAME).so
endif

$(NAME).a: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) && ar -crv $(NAME).a *.o && rm *.o

shared: $(SRC)
	$(CC) -o $(LIB) $(SRC) $(CFLAGS) $(LIBS) $(OSFLAGS)
	
