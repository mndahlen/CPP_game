#include <SFML/Graphics.hpp>
#include "point.h"
#include "keys.h"

using namespace std;

typedef size_t nat;

const nat width = 1024;
const nat height = 768;

bool onKey(bool pressed, sf::Keyboard::Key key, Keys &keys) {
	switch (key) {
	case ::sf::Keyboard::Q:
		return true;
	default:
		keys.onKey(pressed, key);
		break;
	}

	return false;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");
    window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	sf::CircleShape circle(40);
	sf::Vector2f circlePos(300, 300);
	Keys keys;

	bool quit = false;
	while (!quit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				quit = true;
				break;
			case sf::Event::KeyPressed:
				quit |= onKey(true, event.key.code, keys);
				break;
			case sf::Event::KeyReleased:
				quit |= onKey(false, event.key.code, keys);
				break;
			default:
				break;
			}
		}

		window.clear();
		circlePos += keys.direction() * 4.0f;
		circle.setPosition(circlePos);
		window.draw(circle);
		window.display();
	}

	window.close();

	return 0;
}
