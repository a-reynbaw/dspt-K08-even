# File:   Makefile
# Author: Anastasia Marinakou | sdi2400120
# Course: Data Structures and Programing Techniques (Even)


# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Source files - all the .c files in this directory
SOURCES := $(wildcard *.c)

# Header files - all the .h files in this directory
HEADERS := $(wildcard *.h)

# Object files
OBJS = $(SOURCES:.c=.o)

# Output program name
PROGRAM = q5

# Rule to build the executable
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

# Rule to compile .c files into .o files, ensuring header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(PROGRAM) $(OBJS)