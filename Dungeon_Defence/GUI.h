// holds cash, lives, and deals with text
#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
class GUI {
public:
	GUI();
	sf::Font font;
	static sf::Text money;
	static sf::Text lives;
	static sf::Text waveTime;

	void setMoney(int money);
	int getMoney();

	void setLives(int lives);
	int getLives();

	void updateTimer(int Time);

	static void Render(sf::RenderWindow &window);

protected:
	//starter values, can be changed later
	int _lives = 20;
	int _money = 100;
};
