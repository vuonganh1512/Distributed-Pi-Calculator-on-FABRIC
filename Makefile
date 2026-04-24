CC = mpicc
CFLAGS = -O2 -Wall -Wextra -std=c11
TARGET = pi_calc

OBJS = main.o pi_algorithms.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

main.o: main.c pi_algorithms.h utils.h
	$(CC) $(CFLAGS) -c main.c

pi_algorithms.o: pi_algorithms.c pi_algorithms.h
	$(CC) $(CFLAGS) -c pi_algorithms.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(TARGET) *.o

run-small: $(TARGET)
	mpirun -np 2 ./$(TARGET) 1000

run-medium: $(TARGET)
	mpirun -np 4 ./$(TARGET) 1000000

run-large: $(TARGET)
	mpirun -np 8 ./$(TARGET) 50000000
