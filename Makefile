.PHONY: w j

# Detect the OS
UNAME := $(shell uname)

# Default macOS settings
MACOSX_DEPLOYMENT_TARGET = 27.0

SRC_DIR = src
W_SRC_DIR = w/src
J_SRC_DIR = j/src

OBJ_NAME = play
BUILD_DIR = build/debug
CC = g++-14
COMPILER_FLAGS = -std=c++23 -Wall -O0 -g -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
ENGINE_RESOURCE_DIR = engine/resources
W_RESOURCE_DIR = w/resources
ENGINE_SRC_DIR = engine/src
ENGINE_SRC_FILES = $(wildcard $(ENGINE_SRC_DIR)/*.cpp)
W_SRC_FILES = $(wildcard $(W_SRC_DIR)/*.cpp)
J_SRC_FILES = $(wildcard $(J_SRC_DIR)/*.cpp)
W_INCLUDE_PATHS = -Iengine/include -Iw/include -I/opt/homebrew/include
J_INCLUDE_PATHS = -Iengine/include -Ij/include -I/opt/homebrew/include
LIBRARY_PATHS = -L/opt/homebrew/lib
LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf
EXE = 
# Linux-specific settings
LINUX_CC = g++
LINUX_COMPILER_FLAGS = -std=c++23 -Wall -O0 -g
LINUX_INCLUDE_PATHS = -Iw/include -Iengine/include -I/usr/include
W_LINUX_INCLUDE_PATHS = -Iengine/include -Iw/include -I/usr/include
J_LINUX_INCLUDE_PATHS = -Iengine/include -Ij/include -I/usr/include
LINUX_LIBRARY_PATHS = -L/usr/lib
LINUX_LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf

# Windows-specific settings (MinGW / MSYS2)
WINDOWS_CC = x86_64-w64-mingw32-g++
WINDOWS_COMPILER_FLAGS = -std=c++23 -Wall -O0 -g
WINDOWS_INCLUDE_PATHS = -Iengine/include -Iw/include -IC:/msys64/mingw64/include
J_WINDOWS_INCLUDE_PATHS = -Iengine/include -Ij/include -IC:/msys64/mingw64/include
WINDOWS_LIBRARY_PATHS = -LC:/msys64/mingw64/lib
WINDOWS_LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf -lwinmm -lgdi32
WINDOWS_EXE = .exe


# Choose the correct settings based on the OS
ifeq ($(OS),Windows_NT)
    CC = $(WINDOWS_CC)
    COMPILER_FLAGS = $(WINDOWS_COMPILER_FLAGS)
    W_INCLUDE_PATHS = $(WINDOWS_INCLUDE_PATHS)
    J_INCLUDE_PATHS = $(J_WINDOWS_INCLUDE_PATHS)
    LIBRARY_PATHS = $(WINDOWS_LIBRARY_PATHS)
    LINKER_FLAGS = $(WINDOWS_LINKER_FLAGS)
    EXE = $(WINDOWS_EXE)
else ifeq ($(UNAME), Linux)
    # Linux-specific settings
    CC = $(LINUX_CC)
    COMPILER_FLAGS = $(LINUX_COMPILER_FLAGS)
  W_INCLUDE_PATHS = $(W_LINUX_INCLUDE_PATHS)
  J_INCLUDE_PATHS = $(J_LINUX_INCLUDE_PATHS)
    LIBRARY_PATHS = $(LINUX_LIBRARY_PATHS)
    LINKER_FLAGS = $(LINUX_LINKER_FLAGS)
endif

# Build and run the project
j:
	$(CC) $(COMPILER_FLAGS) $(J_INCLUDE_PATHS) $(LIBRARY_PATHS) $(ENGINE_SRC_FILES) $(J_SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/jplay && ./$(BUILD_DIR)/jplay$(EXE)
w:
	$(CC) $(COMPILER_FLAGS) $(W_INCLUDE_PATHS) $(LIBRARY_PATHS) $(ENGINE_SRC_FILES) $(W_SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/wplay && ./$(BUILD_DIR)/wplay$(EXE)
w-debug:
	$(CC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) \
	$(W_INCLUDE_PATHS) $(LIBRARY_PATHS) \
	$(ENGINE_SRC_FILES) $(W_SRC_FILES) \
	$(LINKER_FLAGS) $(SANITIZE_FLAGS) \
	-o $(BUILD_DIR)/wplay_debug
all:
	$(CC) $(COMPILER_FLAGS) $(J_INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME) && ./$(BUILD_DIR)/$(OBJ_NAME)
