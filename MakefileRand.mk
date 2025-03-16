CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRCS = mat_mul_rand.c read_matrix.c 

# Output executable
TARGET = matrix_program_rand

#object files
OBJS = $(SRCS:.c=.o)

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

read_matrix.o: read_matrix.c
	$(CC) $(CFLAGS) -c read_matrix.c

mat_mul_rand.o: mat_mul_rand.c
	$(CC) $(CFLAGS) -c mat_mul_rand.c

clean:
	rm -f *.o $(TARGET)