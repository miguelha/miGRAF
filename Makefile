CC = gcc
CFLAGS = -Wall -I./src

LIB_SRC = src/migraf.c
LIB_HEADER = src/migraf.h
TEST_SRC = test/migraf_test.c
BUILD_DIR = build

all: $(BUILD_DIR)/libmiGRAF.a $(BUILD_DIR)/migraf_test

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(BUILD_DIR)/libmiGRAF.a: $(LIB_SRC) $(LIB_HEADER) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(LIB_SRC) -o $(BUILD_DIR)/migraf.o
	ar rcs $@ $(BUILD_DIR)/migraf.o

$(BUILD_DIR)/migraf_test: $(TEST_SRC) $(BUILD_DIR)/libmiGRAF.a
	$(CC) $(CFLAGS) $(TEST_SRC) -L$(BUILD_DIR) -lmiGRAF -o $@

test: $(BUILD_DIR)/migraf_test
	./$(BUILD_DIR)/migraf_test

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: test all