all:
	clear
	g++ -o main src/main.cpp -lsfml-system -lsfml-window -lsfml-graphics
	./main