CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRCS = mat_mul.c read_matrix.c 

# Output executable
TARGET = matrix_program

#object files
OBJS = $(SRCS:.c=.o)

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

read_matrix.o: read_matrix.c
	$(CC) $(CFLAGS) -c read_matrix.c

mat_mul.o: mat_mul.c
	$(CC) $(CFLAGS) -c mat_mul.c

clean:
	rm -f *.o $(TARGET)