CC = gcc

CFLAGS = -Wall -Werror -g

SRCS = Maze.c 

# Convert the .c filenames to .o to represent object files
OBJS = $(wildcard *.c)

# Name of the executable - change this to your specific executable name
TARGET = maze

# Build the executable by linking object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to convert .c to .o by compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -f $(OBJS) $(TARGET)