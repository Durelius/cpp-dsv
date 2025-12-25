
# Detect the OS
UNAME := $(shell uname)

# Default macOS settings
MACOSX_DEPLOYMENT_TARGET = 27.0
SRC_DIR = src
OBJ_NAME = play
BUILD_DIR = build/debug
CC = g++-14
COMPILER_FLAGS = -std=c++23 -Wall -O0 -g -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE_PATHS = -Iinclude -I/opt/homebrew/include
LIBRARY_PATHS = -Llib -L/opt/homebrew/lib
LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf

# Linux-specific settings
LINUX_CC = g++
LINUX_COMPILER_FLAGS = -std=c++23 -Wall -O0 -g
LINUX_INCLUDE_PATHS = -Iinclude -I/usr/include
LINUX_LIBRARY_PATHS = -Llib -L/usr/lib
LINUX_LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf

# Choose the correct settings based on the OS
ifeq ($(UNAME), Darwin)
    # macOS-specific settings
    CC = g++-14
    COMPILER_FLAGS = -std=c++23 -Wall -O0 -g -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
    INCLUDE_PATHS = -Iinclude -I/opt/homebrew/include
    LIBRARY_PATHS = -Llib -L/opt/homebrew/lib
    LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf
else ifeq ($(UNAME), Linux)
    # Linux-specific settings
    CC = $(LINUX_CC)
    COMPILER_FLAGS = $(LINUX_COMPILER_FLAGS)
    INCLUDE_PATHS = $(LINUX_INCLUDE_PATHS)
    LIBRARY_PATHS = $(LINUX_LIBRARY_PATHS)
    LINKER_FLAGS = $(LINUX_LINKER_FLAGS)
endif

# Build and run the project
all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME) && ./$(BUILD_DIR)/$(OBJ_NAME)
