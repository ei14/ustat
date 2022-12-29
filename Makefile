NAME := ustat
DEP :=

CFLAGS := -O3 -g -Wall -std=c17
LDFLAGS :=
LDLIBS := -lX11 -lasound

CC := gcc
SRC := $(wildcard *.c)
HEAD := $(wildcard *.h)
OBJ := $(SRC:.c=.o)

$(NAME): $(OBJ)

$(OBJ): $(SRC) $(HEAD)

run:
	./$(NAME)

clean:
	rm -f $(NAME)
	rm -f $(wildcard *.o)
	rm -f ~/.local/bin/$(NAME)

install: $(NAME)
	cp $(NAME) ~/.local/bin/

.PHONY: run clean install
