all:
	clear
	ccache g++ -c src/main.cpp -o build/main.o
	ccache g++ build/main.o -lsfml-system -lsfml-window -lsfml-graphics
	./a.out