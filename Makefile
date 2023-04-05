CC := g++
CFLAGS := -Wall -Werror

SRC_DIR := src
OUT_DIR := bin
OBJ_DIR := obj

MAIN_SRCS := $(wildcard $(SRC_DIR)/geometry/*.c)
MAIN_OBJ := $(MAIN_SRCS:$(SRC_DIR)/geometry/%.c=$(OBJ_DIR)/geometry/%.o)

LIB_SRCS := $(wildcard $(SRC_DIR)/libgeometry/*.c)
LIB_OBJ := $(LIB_SRCS:$(SRC_DIR)/libgeometry/%.c=$(OBJ_DIR)/libgeometry/%.o)

LIB_TARGET := $(OUT_DIR)/libgeometry.a
TARGET := $(OUT_DIR)/main

.PHONY: all clean test run
all: $(LIB_TARGET) $(TARGET)

# Main
$(TARGET): $(LIB_TARGET) $(MAIN_OBJ) 
	$(CC) $(CFLAGS) $^ -L$(OUT_DIR) -lgeometry -o $@

$(OBJ_DIR)/geometry/%.o: $(SRC_DIR)/geometry/%.c
	$(CC) $(CFLAGS) -c -I$(SRC_DIR) $< -o $@
# Lib
$(LIB_TARGET): $(LIB_OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/libgeometry/%.o: $(SRC_DIR)/libgeometry/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test
TEST_DIR := test
TEST_TARGET = bin/test
TEST_OBJ = $(OBJ_DIR)/geometry-test/parser_test.o $(OBJ_DIR)/geometry-test/main.o 

$(TEST_TARGET) : $(TEST_OBJ) $(LIB_TARGET)
	$(CC) $(CFLAGS) $^ -o  $@

$(OBJ_DIR)/geometry-test/main.o: $(TEST_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -Ithirdparty -I$(SRC_DIR) -L$(OUT_DIR) -lgeometry -o $@

$(OBJ_DIR)/geometry-test/parser_test.o: $(TEST_DIR)/parser_test.c
	$(CC) $(CFLAGS) -c $< -Ithirdparty -I$(SRC_DIR) -L$(OUT_DIR) -lgeometry -o $@

test: $(LIB_TARGET) $(TEST_TARGET)
	./$(TEST_TARGET)
run:
	./$(OUT_DIR)/main test.txt
