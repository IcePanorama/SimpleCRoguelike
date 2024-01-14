SRC_DIR=src
SRC_FILES=$(SRC_DIR)/*.c
INCL_DIR=include
INCL_FILES=$(INCL_DIR)/*.h
TARGET=main
CFLAGS=-Wpedantic -Wextra -Werror #-Wall 
FORMAT=GNU

all: format $(TARGET) test

$(TARGET): 
	gcc $(SRC_FILES) -I./$(INCL_DIR) -o $(TARGET) $(CFLAGS)

test: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	rm $(TARGET)

format:
	clang-format -style=GNU -i $(SRC_FILES) $(INCL_FILES)
