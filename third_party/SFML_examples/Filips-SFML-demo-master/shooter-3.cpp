#include <SFML/Graphics.hpp>
#include "point.h"

using namespace std;

typedef size_t nat;

const nat width = 1024;
const nat height = 768;

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");
    // window.setKeyRepeatEnabled(false);

	sf::CircleShape circle(40);
	sf::Vector2f pt(300, 300);

	bool quit = false;
	while (!quit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				quit = true;
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case ::sf::Keyboard::Q:
					quit = true;
					break;
				case ::sf::Keyboard::W:
					pt.y -= 10;
					break;
				case ::sf::Keyboard::S:
					pt.y += 10;
					break;
				case ::sf::Keyboard::A:
					pt.x -= 10;
					break;
				case ::sf::Keyboard::D:
					pt.x += 10;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		window.clear();
		circle.setPosition(pt);
		window.draw(circle);
		window.display();
	}

	window.close();

	return 0;
}
