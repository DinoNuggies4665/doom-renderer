all:
	clear
	g++ src/main.cpp -lsfml-system -lsfml-window -lsfml-graphics
	./a.out