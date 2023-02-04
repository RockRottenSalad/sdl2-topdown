

debug:
	clang++ -c src/*.cpp -m64 -g -Wall -I include && clang++ *.o -o bin/debug/main -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lm && ./bin/debug/main
	rm *.o

release:
	clang++ -c src/*.cpp -m64 -O3 -Wall -I include && clang++ *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./bin/release/main
	rm *.o
