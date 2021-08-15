CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include 
LIB		:= lib

LIBRARIES	:= /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_imgcodecs.so /usr/local/lib/libopencv_core.so 
EXECUTABLE	:= Maze


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I/usr/local/include/opencv4 -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
