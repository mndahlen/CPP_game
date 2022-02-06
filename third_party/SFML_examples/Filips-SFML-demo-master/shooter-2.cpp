#include <SFML/Graphics.hpp>

using namespace std;

typedef size_t nat;

const nat width = 1024;
const nat height = 768;

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");

	sf::CircleShape circle(40);
	circle.setPosition(300, 300);

	bool quit = false;
	while (!quit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				quit = true;
				break;
			default:
				break;
			}
		}

		window.clear();
		window.draw(circle);
		window.display();
	}

	window.close();

	return 0;
}


/**
 * Check out:
 * circle.setOrigin(20, 20);
 * circle.setFillCOlor(sf::Color::Red);
 */
