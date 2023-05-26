##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re

CC         = gcc
TARGET     = 42sh

SRC        = $(wildcard src/*.c)
ISRC       = $(wildcard src/internal/*.c)

CFLAGS     += -Wall -c -I./include/ -g3 -fno-builtin-memset -o

OBJECTS    = $(SRC:.c=.o)
IOBJECTS   = $(ISRC:.c=.o)

all: $(TARGET)

$(TARGET): $(IOBJECTS) $(OBJECTS)
	@echo "ld $(TARGET)"
	@$(CC) -o $@ $^

src/%.o: src/%.c
	@echo "cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

src/internal/%.o: src/internal/%.c
	@echo "cc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@rm -f $(IOBJECTS)

fclean: clean
	@rm -f $(TARGET)

re: fclean all
