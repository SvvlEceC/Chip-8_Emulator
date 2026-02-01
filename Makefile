CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17 `sdl2-config --cflags`
LIBS = `sdl2-config --libs`
BIN_DIR = bin

CORE_SRC = src/chip8.cpp src/cpu.cpp src/display.cpp src/instructions.cpp
MAIN_SRC = src/main.cpp

$(BIN_DIR)/chip8_exe: $(CORE_SRC) $(MAIN_SRC) 
			@mkdir -p $(BIN_DIR) 
			$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

run: $(BIN_DIR)/chip8_exe 
		./$(BIN_DIR)/chip8_exe $(ROM)

brix: $(BIN_DIR)/chip8_exe 
		./$(BIN_DIR)/chip8_exe roms/Brix.ch8

ibm: $(BIN_DIR)/chip8_exe 
		./$(BIN_DIR)/chip8_exe "roms/IBM Logo.ch8"

pong: $(BIN_DIR)/chip8_exe 
		./$(BIN_DIR)/chip8_exe roms/Pong.ch8

tetris: $(BIN_DIR)/chip8_exe 
		./$(BIN_DIR)/chip8_exe roms/tetris.ch8

test%: tests/test%.cpp $(CORE_SRC) 
		@mkdir -p $(BIN_DIR) 
		$(CXX) $(CXXFLAGS) $^ -o $(BIN_DIR)/$@ $(LIBS) 
		./$(BIN_DIR)/$@

clean: 
	rm -f $(BIN_DIR)