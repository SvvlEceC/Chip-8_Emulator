all:
	g++ -Iinclude src/*.cpp -o bin/chip8_emu `sdl2-config --cflags --libs`

run:
	./bin/chip8_emu