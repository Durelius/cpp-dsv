SRC_DIR = src
OBJ_NAME = play
BUILD_DIR = build/debug
CC = g++-14
MACOS_TARGET = -mmacosx-version-min=26.0
COMPILER_FLAGS = -std=c++23 -Wall -O0 -g
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(MACOS_TARGET)
INCLUDE_PATHS = -Iinclude -I/opt/homebrew/include
LIBRARY_PATHS = -Llib -L/opt/homebrew/lib
LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME) && ./$(BUILD_DIR)/$(OBJ_NAME)
