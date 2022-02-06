#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

typedef size_t nat;

const nat width = 1024;
const nat height = 768;

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");

	bool quit = false;
	while (!quit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				quit = true;
				break;
			default:
				cout << "Event: " << event.type << endl;
				break;
			}
		}

		window.clear();
		window.display();
	}

	window.close();

	return 0;
}
