# ASCII-Sky-War Makefile

# Paths
# $(shell pwd)
DIR=.
LIB_DIR=$(DIR)/lib
INCLUDE_DIR=$(DIR)/include
SRC_DIR=$(DIR)/src
BUILD_DIR=$(DIR)/build
# Objects
LIB = -lm -lncurses -lcurl
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# Complier options
CC = gcc
CFLAGS=-Wall
LDFLAGS=$(LIB)

# Compile targets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -I $(INCLUDE_DIR) -o $@

build: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BUILD_DIR)/skywar

clean:
	rm -rf $(OBJ)

# Bypass files with the same name
.PHONY: build clean
