# MAKEFILE FOR FINDING ROOTS
# Assumes main.cpp, findRoots.cpp, and findRoots.h are in the same directory

# List vairables here
CC = g++
CFLAGS = -Wall -Werror
INCLDIR = .

# Main target, run with  $ make
all: findRoots

# Run option, compiles project and executes the output filename
run: findRoots
	./$^

# Compile project. $@ gets the target name, and $^ uses all arguments
findRoots: main.o findRoots.o
	$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ $^


# For all .o files. $< uses the first argument
%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLDIR) -c $<


# Clean .o files and executable
# BE CAREFUL WITH THE -f FLAG!!!!!
clean:
	rm -f *.o findRoots
