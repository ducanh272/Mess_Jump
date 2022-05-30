all:
	g++ -std=c++17 -D MAC ./src/*.cpp -I./include `sdl2-config --libs -cflags` -lSDL2_ttf -lSDL2_mixer -lSDL2_image