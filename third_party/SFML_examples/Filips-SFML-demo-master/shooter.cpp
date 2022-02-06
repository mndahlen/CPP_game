#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "point.h"
#include "keys.h"

using namespace std;

typedef size_t nat;

// const nat width = 1920;
// const nat height = 1080;
const nat width = 1024;
const nat height = 768;

template <class T>
using Ptr = unique_ptr<T>;

class World;
class Entity;

/**
 * Describes how an entity behaves in the world. 'tick' is called once before
 * each frame, allowing the Movement to update the associated Entity.
 */
class Movement {
public:
	virtual ~Movement() {}
	virtual bool tick(sf::Time time, World &world, Entity &owner) = 0;
};

/**
 * Move things in a straight line.
 */
class LinearMovement : public Movement {
public:
	LinearMovement(sf::Vector2f to, sf::Time time, bool remove = false)
		: from{}, to{to}, time{time}, distance{0}, remove{remove}, cumulated{} {}

	LinearMovement(sf::Vector2f to, float distance, sf::Time time, bool remove = false)
		: from{}, to{to}, time{time}, distance{distance}, remove{remove}, cumulated{} {}

	sf::Vector2f from, to;
	sf::Time time;
	float distance;
	bool remove;

	bool tick(sf::Time time, World &world, Entity &owner) override;
private:
	sf::Time cumulated;
};

/**
 * Move things in a sine wave along a curved line towards the edge of the screen.
 */
class SineMove : public Movement {
public:
	SineMove(sf::Time time) : time{time}, cumulated{}, x{} {}

	sf::Time time;
	sf::Time cumulated;
	float x;

	bool tick(sf::Time time, World &world, Entity &owner) override;
};

/**
 * Cause the Entity to shoot other entities at a regular interval. Allows
 * attaching another movement to actually move the entity.
 */
class Shooter : public Movement {
public:
	Shooter(sf::Time interval, function<Entity *(sf::Vector2f)> create, Movement *move)
		: interval{interval}, create{create}, move{move}, cumulated{} {}

	sf::Time interval;
	function<Entity *(sf::Vector2f)> create;
	Ptr<Movement> move;

	bool tick(sf::Time time, World &world, Entity &owner) override;

private:
	sf::Time cumulated;
};

/**
 * Controlled by the player.
 */
class Player : public Movement {
public:
	Player(float speed) : speed{speed} {}

	bool tick(sf::Time time, World &world, Entity &owner) override;

private:
	float speed;
};

/**
 * An entity, ie. something that is drawn to the screen. For now, it has a position and a radius.
 */
class Entity {
public:
	// Center position and radius.
	sf::Vector2f pos;
	float radius;

	// Create.
	Entity(sf::Vector2f pos, float radius, Movement *move = nullptr)
		: pos{pos}, radius{radius}, movement{move} {}

	virtual ~Entity() {}

	// Tick
	virtual bool tick(sf::Time time, World &world);

	// Render
	virtual void render(sf::RenderWindow &window) = 0;

	// Movement.
	Ptr<Movement> movement;
};

/**
 * An entity that is drawn using a texture from a file on disk. Caches textures, so that the same
 * texture is only loaded once.
 */
class Textured : public Entity {
public:
	Textured(sf::Vector2f pos, string name, Movement *move = nullptr)
		: Entity{pos, 0, move}, shape{} {
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

	void render(sf::RenderWindow &window) override;

	static map<string, Ptr<sf::Texture>> textures;

private:
	sf::RectangleShape shape;
};

/**
 * An entity which is not drawn at all, but spawns another entity after a given amount of time.
 */
class Delay : public Entity {
public:
	// Create.
	Delay(sf::Vector2f pos, Entity *create, sf::Time delay)
		: Entity{pos, 0.0f}, create{create}, delay{delay}, cumulated{} {}

	// Tick
	bool tick(sf::Time time, World &world) override;

	// Render
	void render(sf::RenderWindow &) override {}

private:
	Ptr<Entity> create;
	sf::Time delay;
	sf::Time cumulated;
};

/**
 * Adds a particle system to another entity.
 */
class Particles : public Entity {
public:
	// Create.
	Particles(Entity *real, nat spawn, float distance, sf::Time live, sf::Color color)
		: Entity{real->pos, 0.0f}, real{real}, spawn{spawn},
		  distance{distance}, live{live}, color{color}, particles{} {}

	bool tick(sf::Time time, World &world) override;
	void render(sf::RenderWindow &window) override;

private:
	Ptr<Entity> real;
	nat spawn;
	float distance;
	sf::Time live;
	sf::Color color;

	struct Particle {
		float life{}; // 0-1
		sf::Vector2f pos{};
		sf::Vector2f delta{};
	};

	vector<Particle> particles;
};

/**
 * The world. Contains a set of entities, and is in chare of drawing and moving these.
 */
class World {
public:
	World(sf::RenderWindow &window)
		: quit{false}, keys{}, window{window}, entities{} {}

	// Quit?
	bool quit;

	// Currently pressed keys.
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
 * Entity implementation:
 */

bool Entity::tick(sf::Time time, World &world) {
	if (movement)
		return movement->tick(time, world, *this);
	else
		return false;
}

/**
 * Textured implementation:
 */

map<string, Ptr<sf::Texture>> Textured::textures;

void Textured::render(sf::RenderWindow &window) {
	shape.setPosition(pos.x, pos.y);
	window.draw(shape);
}

/**
 * LinearMovement implementation:
 */

bool LinearMovement::tick(sf::Time delta, World &, Entity &owner) {
	if (cumulated == sf::Time()) {
		from = owner.pos;
		if (distance > 0) {
			sf::Vector2f dir = normalize(to - from);
			to = from + dir*distance;
		}
	}

	float dur = float(cumulated.asMilliseconds()) / float(time.asMilliseconds());
	if (dur > 1.0f) {
		owner.pos = to;
		return remove;
	} else {
		owner.pos = from * (1.0f - dur) + to * dur;
		cumulated += delta;
		return false;
	}
}

/**
 * SineMove implementation:
 */

bool SineMove::tick(sf::Time delta, World &, Entity &owner) {
	if (cumulated == sf::Time()) {
		x = owner.pos.x;
	}

	float t = float(cumulated.asMilliseconds()) / float(time.asMilliseconds());
	owner.pos.y = height * t;

	float amplitude = 1.0f - t;
	owner.pos.x = x + sin((t + x / width) * 12) * amplitude * width / 4.0f;
	if (x > width / 2) {
		owner.pos.x += (width - x) * t;
	} else {
		owner.pos.x -= x * t;
	}

	if (t >= 1.0f)
		return true;

	cumulated += delta;
	return false;
}

/**
 * Shooter implementation:
 */

bool Shooter::tick(sf::Time delta, World &world, Entity &owner) {
	if (cumulated >= interval) {
		cumulated -= interval;
		world.add(create(owner.pos));
	}
	cumulated += delta;

	return move->tick(delta, world, owner);
}

/**
 * Player implementation:
 */

bool Player::tick(sf::Time delta, World &world, Entity &owner) {
	sf::Vector2f dir = world.keys.direction();
	float v = delta.asMilliseconds() / 1000.0;
	owner.pos = owner.pos + dir*v*speed;

	return false;
}

/**
 * Delay implementation:
 */

bool Delay::tick(sf::Time delta, World &world) {
	if (cumulated > delay) {
		world.add(create);
		return true;
	}
	cumulated += delta;
	return false;
}

/**
 * Particles implementation:
 */

bool Particles::tick(sf::Time time, World &world) {
	float advance = time.asMilliseconds() / float(live.asMilliseconds());

	nat to = 0;
	for (auto &p : particles) {
		p.life += advance;
		if (p.life <= 1.0f)
			particles[to++] = p;
	}

	// Shrink.
	particles.resize(to);

	// Spawn new.
	for (nat i = 0; i < spawn; i++) {
		float angle = 2 * M_PI * float(rand()) / float(RAND_MAX);
		float dist = distance + distance/3 * float(rand()) / float(RAND_MAX);
		Particle p = {
			real->radius / dist,
			real->pos,
			sf::Vector2f(sin(angle), cos(angle)) * dist,
		};
		particles.push_back(p);
	}

	return real->tick(time, world);
}

void Particles::render(sf::RenderWindow &window) {
	vector<sf::Vertex> r(particles.size());

	for (nat i = 0; i < r.size(); i++) {
		Particle &p = particles[i];

		sf::Vector2f pos = p.pos + p.delta*p.life;
		sf::Color c = color;
		c.a = (1.0f - p.life)*255.0f;
		r[i] = sf::Vertex(pos, c);
	}

	window.draw(&r[0], r.size(), sf::PrimitiveType::Points);

	real->render(window);
}

/**
 * World implementation:
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

Entity *createShooter(float x, nat speed, bool center) {
	float w = center ? width / 2 : x;
	Movement *move = new SineMove(sf::seconds(4));
	Shooter *shooter = new Shooter(sf::milliseconds(speed), [w](sf::Vector2f p) {
									return
									new Particles(
										new Textured(p, "bullet.png",
													new LinearMovement(sf::Vector2f(w, height), height*2, sf::seconds(5), true)),
										10,
										70.0f,
										sf::milliseconds(800),
										sf::Color::Yellow);
								}, move);
	return
		new Particles(
			new Textured(sf::Vector2f(x, 0), "green.png", shooter),
			10,
			80.0f,
			sf::milliseconds(1200),
			sf::Color::Green);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Shoot");
	window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

	World world(window);
	sf::Clock clock;

	// for (nat i = 0; i < 1000; i++) {
	// 	float x = rand() % width;
	// 	nat delay = rand() % 60000;
	// 	nat speed = rand() % 200 + 400;
	// 	world.add(new Delay(sf::Vector2f(x, 0), createShooter(x, speed, rand() % 2 == 1), sf::milliseconds(delay)));
	// }

	world.add(new Textured(sf::Vector2f(width / 2, height * 4 / 5), "player.png", new Player(300)));

	// world.add(
	// 	new Particles(
	// 		new Textured(sf::Vector2f(width / 2, height * 4 / 5), "player.png", new Player(300)),
	// 		20,
	// 		100.0f,
	// 		sf::milliseconds(1000),
	// 		sf::Color::Blue));

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

		nat z = rand() % 100;
		if (z < 8) {
			float x = rand() % width;
			nat speed = rand() % 300 + 300;
			world.add(createShooter(x, speed, rand() % 2 == 1));
		}

		window.clear();
		world.tick(clock.restart());
		world.render();
		window.display();
	}

	window.close();

	return 0;
}
