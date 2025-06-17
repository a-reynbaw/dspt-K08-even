# File:   Makefile
# Author: Anastasia Marinakou | sdi2400120
# Course: Data Structures and Programing Techniques (Even)

# Brief: use this Makefile to compile question4.c and test_modules.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Source files
SOURCES_MAIN = main.c PQImplementation.c
SOURCES_TEST = test_module.c PQImplementation.c

# Header files
HEADERS = PQTypes.h PQInterface.h

# Object files
OBJS_MAIN = $(SOURCES_MAIN:.c=.o)
OBJS_TEST = $(SOURCES_TEST:.c=.o)

# Output program name
PROGRAM_MAIN = q4
PROGRAM_TEST = test

# Rule to build the main executable
$(PROGRAM_MAIN): $(OBJS_MAIN)
	$(CC) $(CFLAGS) $(OBJS_MAIN) -o $(PROGRAM_MAIN)

# Rule to build the test executable
$(PROGRAM_TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) $(OBJS_TEST) -o $(PROGRAM_TEST)

# Rule to compile .c files into .o files, ensuring header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(PROGRAM_MAIN) $(PROGRAM_TEST) $(OBJS_MAIN) $(OBJS_TEST)