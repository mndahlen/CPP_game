#pragma once
#include <SFML/Graphics.hpp>
#include "point.h"

class Keys {
public:
	bool up, down, left, right;

	Keys() : up(false), down(false), left(false), right(false) {}

	void onKey(bool pressed, sf::Keyboard::Key key) {
		switch (key) {
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			up = pressed;
			break;
		case sf::Keyboard::Down:
		case ::sf::Keyboard::S:
			down = pressed;
			break;
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
			left = pressed;
			break;
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
			right = pressed;
			break;
		default:
			break;
		}
	}

	sf::Vector2f direction() const {
		sf::Vector2f dir;
		if (up)
			dir.y -= 1.0f;
		if (down)
			dir.y += 1.0f;
		if (left)
			dir.x -= 1.0f;
		if (right)
			dir.x += 1.0f;
		// return dir;
		return normalize(dir);
	}

	// sf::Vector2f direction() const {
	// 	sf::Vector2f dir;
	// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	// 		dir.y -= 1.0f;
	// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	// 		dir.y += 1.0f;
	// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	// 		dir.x -= 1.0f;
	// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	// 		dir.x += 1.0f;
	// 	return normalize(dir);
	// }
};
