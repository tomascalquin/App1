CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = app1.o lenguajesyparadigmas1.o
TARGET = app1

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
