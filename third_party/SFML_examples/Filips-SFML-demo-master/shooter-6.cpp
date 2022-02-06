#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "point.h"
#include "keys.h"

using namespace std;

typedef size_t nat;

const nat width = 1024;
const nat height = 768;

template <class T>
using Ptr = unique_ptr<T>;

class World;

class Entity {
public:
	// Center position and radius.
	sf::Vector2f pos;
	float radius;

	// Create.
	Entity(sf::Vector2f pos, float radius)
		: pos{pos}, radius{radius} {}

	// Destroy.
	virtual ~Entity() {}

	// Tick.
	virtual bool tick(sf::Time time, World &world);

	// Render.
	virtual void render(sf::RenderWindow &window) = 0;
};

bool Entity::tick(sf::Time, World &) {
	return false;
}


/**
 * Entity drawn using a texture from a file on disk.
 */
class Textured : public Entity {
public:
	Textured(sf::Vector2f pos, string name);

	void render(sf::RenderWindow &window) override;

	static map<string, Ptr<sf::Texture>> textures;

private:
	sf::RectangleShape shape;
};

map<string, Ptr<sf::Texture>> Textured::textures;

Textured::Textured(sf::Vector2f pos, string name)
		: Entity{pos, 0}, shape{} {
	auto i = textures.find(name);
	sf::Texture *t;
	if (i == textures.end()) {
		t = new sf::Texture();
		if (!t->loadFromFile(name))
			throw std::logic_error("Failed to load texture!");
		textures.insert(make_pair(name, Ptr<sf::Texture>(t)));
	} else {
		t = i->second.get();
	}

	auto size = t->getSize();
	shape.setSize(sf::Vector2f(size.x, size.y));
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setTexture(t);
	radius = sqrt((size.x + size.y) / 2);
}

void Textured::render(sf::RenderWindow &window) {
	shape.setPosition(pos.x, pos.y);
	window.draw(shape);
}


/**
 * The world. Contains all entities.
 */
class World {
public:
	World(sf::RenderWindow &window)
		: quit{false}, keys{}, window{window}, entities{} {}

	// Quit?
	bool quit;

	// Pressed keys.
	Keys keys;

	// Key press/release.
	void onKeyPress(sf::Keyboard::Key key);
	void onKeyRelease(sf::Keyboard::Key key);

	// Update the world!
	void tick(sf::Time time);

	// Render the world!
	void render();

	// Add entities.
	void add(Entity *entity) { entities.push_back(Ptr<Entity>(entity)); }
	void add(Ptr<Entity> &entity) { entities.push_back(std::move(entity)); }

private:
	sf::RenderWindow &window;

	// Entities.
	vector<Ptr<Entity>> entities;
};

/**
 * World.
 */

void World::onKeyPress(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Q:
		quit = true;
		break;
	default:
		keys.onKey(true, key);
		break;
	}
}

void World::onKeyRelease(sf::Keyboard::Key key) {
	switch (key) {
		// Nothing needed here.
	default:
		keys.onKey(false, key);
		break;
	}
}

void World::tick(sf::Time time) {
	for (nat i = 0; i < entities.size(); i++) {
		if (entities[i]->tick(time, *this)) {
			entities.erase(entities.begin() + i);
			i--;
		}
	}
}

void World::render() {
	for (auto &i : entities) {
		i->render(window);
	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");
	window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

	World world(window);

	world.add(new Textured(sf::Vector2f(300, 300), "player.png"));

	sf::Clock clock;
	while (!world.quit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				world.quit = true;
				break;
			case sf::Event::KeyPressed:
				world.onKeyPress(event.key.code);
				break;
			case sf::Event::KeyReleased:
				world.onKeyRelease(event.key.code);
				break;
			default:
				break;
			}
		}

		window.clear();
		world.tick(clock.restart());
		world.render();
		window.display();
	}

	window.close();

	return 0;
}
