#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

typedef size_t nat;

const vector<sf::Color> colors = {
	sf::Color::Black, // Empty
	sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::White
};

const nat width = 7;
const nat height = 30;

const nat cx = 30;
const nat cy = 30;

nat board[height][width];

typedef vector<vector<nat>> Piece;

const vector<Piece> pieces = {
	{
		{ 1, 1 },
		{ 1, 1 },
	},
	{
		{ 2, 0 },
		{ 2, 2 },
		{ 0, 2 },
	},
	{
		{ 0, 3 },
		{ 3, 3 },
		{ 3, 0 },
	},
	{
		{ 4 },
		{ 4 },
		{ 4 },
		{ 4 },
	},
	{
		{ 0, 5, 0 },
		{ 5, 5, 5 },
	},
};

void put(const Piece &p, nat xp, nat yp) {
	for (nat y = 0; y < p.size(); y++) {
		for (nat x = 0; x < p[y].size(); x++) {
			if (p[y][x] != 0 && x + xp < width && y + yp < height && board[y + yp][x + xp] == 0) {
				board[y + yp][x + xp] = p[y][x];
			}
		}
	}
}

void erase(const Piece &p, nat xp, nat yp) {
	for (nat y = 0; y < p.size(); y++) {
		for (nat x = 0; x < p[y].size(); x++) {
			if (x + xp < width && y + yp < height && board[y + yp][x + xp] == p[y][x]) {
				board[y + yp][x + xp] = 0;
			}
		}
	}
}

bool possible(const Piece &p, nat xp, nat yp) {
	for (nat y = 0; y < p.size(); y++) {
		for (nat x = 0; x < p[y].size(); x++) {
			if (p[y][x] != 0) {
				if (x + xp >= width || y + yp >= height)
					return false;
				if (board[y + yp][x + xp] != 0)
					return false;
			}
		}
	}
	return true;
}

nat posx = 0, posy = 0;
Piece piece;
bool gameOver = false;

bool fullLine(nat y) {
	for (nat x = 0; x < width; x++) {
		if (board[y][x] == 0)
			return false;
	}
	return true;
}

void moveDown(nat start) {
	for (nat y = start; y > 0; y--) {
		for (nat x = 0; x < width; x++) {
			board[y][x] = board[y-1][x];
		}
	}
}

void checkLines() {
	for (nat y = 0; y < height; y++) {
		if (fullLine(y)) {
			moveDown(y);
		}
	}
}

void newPiece() {
	piece = pieces[rand() % pieces.size()];
	posx = (width - piece[0].size()) / 2;
	posy = 0;

	if (!possible(piece, posx, posy))
		gameOver = true;
}

void move() {
	if (piece.empty()) {
		newPiece();
	} else {
		erase(piece, posx, posy);
		if (possible(piece, posx, posy + 1)) {
			posy++;
		} else {
			put(piece, posx, posy);
			checkLines();
			piece = Piece();
		}
	}

	put(piece, posx, posy);
}

Piece rotate(const Piece &p) {
	nat h = p.size();
	if (h == 0)
		return Piece();

	nat w = p[0].size();
	Piece r(w, vector<nat>(h, 0));

	for (nat x = 0; x < w; x++)
		for (nat y = 0; y < h; y++)
			r[x][h-y-1] = p[y][x];

	return r;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(cx * width, cy * height), "Tetris");
	window.setVerticalSyncEnabled(true);

	vector<sf::RectangleShape> shapes;
	for (nat i = 0; i < colors.size(); i++) {
		sf::RectangleShape s(sf::Vector2f(cx, cy));
		s.setFillColor(colors[i]);
		shapes.push_back(s);
	}

	memset(board, 0, sizeof(board));

	sf::Clock clock;
	sf::Time targetDelay(sf::milliseconds(10));

	nat ticks = 0;

	for (nat x = 0; x < width; x++)
		board[height-1][x] = 3;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Q:
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Left:
					if (!gameOver) {
						if (posx >= 1) {
							erase(piece, posx, posy);
							if (possible(piece, posx - 1, posy))
								posx--;
							put(piece, posx, posy);
						}
					}
					break;
				case sf::Keyboard::Right:
					if (!gameOver) {
						erase(piece, posx, posy);
						if (possible(piece, posx + 1, posy))
							posx++;
						put(piece, posx, posy);
					}
					break;
				case sf::Keyboard::Down:
					if (!gameOver) {
						erase(piece, posx, posy);
						if (possible(piece, posx, posy + 1))
							posy++;
						put(piece, posx, posy);
					}
					break;
				case sf::Keyboard::M:
					if (!gameOver) {
						erase(piece, posx, posy);
						Piece r = rotate(piece);
						if (possible(r, posx, posy))
							piece = r;
						put(piece, posx, posy);
					}
					break;
				case sf::Keyboard::N:
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		if (++ticks == 40 && !gameOver) {
			ticks = 0;

			move();
		}

		window.clear();

		for (nat x = 0; x < width; x++) {
			for (nat y = 0; y < height; y++) {
				sf::RectangleShape &shape = shapes[board[y][x]];
				shape.setPosition(x * cx, y * cy);
				window.draw(shape);
			}
		}

		window.display();

		// sf::Time delay = clock.restart();
		// if (delay < targetDelay)
		// 	sf::sleep(targetDelay - delay);
	}

	return 0;
}
