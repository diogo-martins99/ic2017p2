###
### First part of a Makefile:
### Define required variables
###

### Variables used by implicit rules:
### https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

# C compiler to use
CC=gcc
# Compiler flags
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g
# Linker library location flags (e.g. -L)
LDFLAGS=
# Linker library flags (e.g. -l)
LDLIBS=

### Regular variables

# Name of program
PROGRAM=fried_brains

###
### Second part of a Makefile:
### Rules to build our example
###

# Rule to generate executable program - by default first target in the makefile
# is generated when "make" is executed. Because no explicit recipe is given,
# the "make" program will use the implicit rule for linking all object files
# into an executable program.
$(PROGRAM): $(PROGRAM).o simple_showworld.o

# Rule to generate program object. Again, because no explicit recipe is given,
# "make" will use an implicit rule for properly compiling $(PROGRAM).o.
$(PROGRAM).o: $(PROGRAM).c simple_showworld.h showworld.h

# Rule to generate simple_showworld.o object. Again, because no explicit recipe
# is given, "make" will use an implicit rule for properly compiling
# simple_showworld.o.
simple_showworld.o: simple_showworld.c simple_showworld.h

# The followin rule cleans all compiled (objects) and linked (executable
# program) files. Because "clean" is not actually the name of a file, it is
# good practice to specify it as a "phony" target (avoiding conflict with a
# file of the same name and improving performance). In this case, an explicit
# recipe is given, so make will not try to determine an implicit one.
.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
