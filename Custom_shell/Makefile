# Compiler
CC = gcc
CFLAGS = -Wall -Werror -g

# for all
all: shell fact

# for shell
$(shell): shell.c
	$(CC) $(CFLAGS) -o shell shell.c

# For factorial
$(fact): fact.c
	$(CC) $(CFLAGS) -o fact fact.c

# Clean files
clean:
	rm -f shell fact

