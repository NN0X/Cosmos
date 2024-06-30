CXX = gcc
CFLAGS = -O3 -Wall -Wextra -Wpedantic
SRC = src
OUT = main

all:
	$(CXX) $(CFLAGS) $(SRC)/*.c -o $(OUT)

clean:
	rm -f $(OUT)