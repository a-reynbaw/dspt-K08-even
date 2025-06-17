# File:   Makefile
# Author: Anastasia Marinakou | sdi2400120
# Course: Data Structures and Programing Techniques (Even)

# Brief: use this Makefile to create easily the executable

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic 

# Source files
SOURCES = kdTreeImplementation.c ListImplementation.c PointImplementation.c RangeImplementation.c main.c

# Header files
HEADERS = kdTreeInterface.h ListInterface.h RangeInterface.h PointInterface.h

# Object files
OBJS = $(SOURCES:.c=.o)

# Output program name
PROGRAM = q6

# Rule to build the executable
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) -lm

# Rule to compile .c files into .o files, ensuring header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

# Clean rule
clean:
	rm -f $(PROGRAM) $(OBJS)