#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <math.h>

// SFML and Other Main Stuff
sf::RenderWindow window; // The Window
sf::Event event; // For Handling Window Events
sf::VertexArray points; // All the Points on the Screen
const float SPEED = 5, SPEED2 = SPEED / 2, SPEED3 = SPEED / 3; // The Amount of Pixels each Point Moves each Frame

// A Single Point on the Screen
struct Point {
	float x = 0, y = 0;
};

// A Shape with Three Points
struct Triangle {
	Point a, b, c;	
};

// A Shape made out of Triangles
struct Square {
	float x, y, z;
	Triangle tri1, tri2;

	Square(float _x, float _y, float _z) {
		this->x = _x;
		this->y = _y;
		this->z = _z;
		this->tri1.a.x = x - z,	this->tri1.a.y = y - z;
		this->tri1.b.x = x + z,	this->tri1.b.y = y - z;
		this->tri1.c.x = x - z,	this->tri1.c.y = y + z;
		this->tri2.a.x = x + z,	this->tri2.a.y = y + z;
		this->tri2.b.x = x - z,	this->tri2.b.y = y + z;
		this->tri2.c.x = x + z,	this->tri2.c.y = y - z;
	}
};

// Plotting Points on the Screen
void plot(float _x, float _y, float _x2, float _y2, sf::Color _color = sf::Color::White) {
	points.append(sf::Vertex(sf::Vector2f(_x, _y), _color));
	points.append(sf::Vertex(sf::Vector2f(_x2, _y2), _color));
}

int main() {

	// Setting Up the Window
	window.create(sf::VideoMode(800, 600), "Graphics", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(75);
	window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400, sf::VideoMode::getDesktopMode().height / 2 - 300));

	// Setting the Vertices to Connect via Lines
	points.setPrimitiveType(sf::Lines);

	// Declaring All the Shapes
	Square square(400, 300, 50);

	// Program Loop
	while (window.isOpen()) {
		// Polling Window Events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						window.close();
						break;
				}
			}
		}

		// Controls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			square.x += SPEED;
			square.tri1.a.x += SPEED;
			square.tri1.b.x += SPEED;
			square.tri1.c.x += SPEED;
			square.tri2.a.x += SPEED;
			square.tri2.b.x += SPEED;
			square.tri2.c.x += SPEED;
			if (square.x >= 400) {
				square.tri1.b.y -= SPEED3;
				square.tri2.a.y += SPEED3;
				square.tri2.c.y -= SPEED3;
			}
			else {
				square.tri1.a.y += SPEED3;
				square.tri1.c.y -= SPEED3;
				square.tri2.b.y -= SPEED3;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			square.x -= SPEED;
			square.tri1.a.x -= SPEED;
			square.tri1.b.x -= SPEED;
			square.tri1.c.x -= SPEED;
			square.tri2.a.x -= SPEED;
			square.tri2.b.x -= SPEED;
			square.tri2.c.x -= SPEED;
			if (square.x < 400) {
				square.tri1.a.y -= SPEED3;
				square.tri1.c.y += SPEED3;
				square.tri2.b.y += SPEED3;
			}
			else {
				square.tri1.b.y += SPEED3;
				square.tri2.a.y -= SPEED3;
				square.tri2.c.y += SPEED3;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			square.tri1.a.x -= SPEED3,	square.tri1.a.y -= SPEED3;
			square.tri1.b.x += SPEED3,	square.tri1.b.y -= SPEED3;
			square.tri1.c.x -= SPEED3,	square.tri1.c.y += SPEED3;
			square.tri2.a.x += SPEED3,	square.tri2.a.y += SPEED3;
			square.tri2.b.x -= SPEED3,	square.tri2.b.y += SPEED3;
			square.tri2.c.x += SPEED3,	square.tri2.c.y -= SPEED3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			square.tri1.a.x += SPEED3,	square.tri1.a.y += SPEED3;
			square.tri1.b.x -= SPEED3,	square.tri1.b.y += SPEED3;
			square.tri1.c.x += SPEED3,	square.tri1.c.y -= SPEED3;
			square.tri2.a.x -= SPEED3,	square.tri2.a.y -= SPEED3;
			square.tri2.b.x += SPEED3,	square.tri2.b.y -= SPEED3;
			square.tri2.c.x -= SPEED3,	square.tri2.c.y += SPEED3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			square.tri1.a.x += SPEED;
			square.tri1.b.x += SPEED;
			square.tri1.c.x += SPEED;
			square.tri2.a.x += SPEED;
			square.tri2.b.x += SPEED;
			square.tri2.c.x += SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			square.tri1.a.x -= SPEED;
			square.tri1.b.x -= SPEED;
			square.tri1.c.x -= SPEED;
			square.tri2.a.x -= SPEED;
			square.tri2.b.x -= SPEED;
			square.tri2.c.x -= SPEED;
		}

		// Adding the Points
		points.clear();
		plot(square.tri1.a.x, square.tri1.a.y, square.tri1.b.x, square.tri1.b.y);
		plot(square.tri1.b.x, square.tri1.b.y, square.tri1.c.x, square.tri1.c.y);
		plot(square.tri1.c.x, square.tri1.c.y, square.tri1.a.x, square.tri1.a.y);
		plot(square.tri2.a.x, square.tri2.a.y, square.tri2.b.x, square.tri2.b.y);
		plot(square.tri2.b.x, square.tri2.b.y, square.tri2.c.x, square.tri2.c.y);
		plot(square.tri2.c.x, square.tri2.c.y, square.tri2.a.x, square.tri2.a.y);

		// Draw Lines
		window.clear();
		window.draw(points);
		window.display();
	}
	return 0;
}