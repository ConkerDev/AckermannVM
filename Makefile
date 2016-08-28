# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -lm	 links math library
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c99 -Wall -g
LATEFLAGS = -lm

# the build target executable:
EXECUTABLE = vm
LIB1 = stack

all: $(LIB1).o $(EXECUTABLE)

$(EXECUTABLE) : $(LIB1).o $(EXECUTABLE).o 
	$(CC) $(CFLAGS) $(LIB1).o $(EXECUTABLE).o -o $(EXECUTABLE) $(LATEFLAGS)

$(EXECUTABLE).o : $(EXECUTABLE).c
	$(CC) $(CFLAGS) -c $(EXECUTABLE).c -o $(EXECUTABLE).o

$(LIB1).o: $(LIB1).c
	$(CC) $(CFLAGS) -c $(LIB1).c -o $(LIB1).o 
	
.PHONY : clean

clean:
	$(RM) $(EXECUTABLE)
	$(RM) $(EXECUTABLE).o
	$(RM) $(LIB1).o
