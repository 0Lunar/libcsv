CC = gcc
CFLAGS = -Iinclude
SRC = src/csv.c test/main.c
OBJ = $(SRC:.c=.o)
EXEC = testcsv

test: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC) *.csv

