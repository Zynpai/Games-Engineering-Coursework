// holds cash, lives, and deals with text
#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "scene.h"
//#include "cmp_player_movement.h"
using namespace std;

class GUI {
public:
	GUI();
	sf::Font font;
	static sf::Text money;
	static sf::Text lives;
	static sf::Text waveTime;

	//headers for different sections
	static sf::Text Towers;
	static sf::Text Abilities;

	static sf::Text wallCooldown;
	static sf::Text tremorCooldown;

	static sf::Text Basic;
	static sf::Text Fire;
	static sf::Text Lightning;

	void setMoney(int money);
	int getMoney();
	

	void setLives(int lives);
	int getLives();

	void updateTimer(int Time);
	void updateWall(int Time);
	void updateTremor(int Time);

	void update(double dt);

	static void Render(sf::RenderWindow &window);

	
protected:
	//starter values, can be changed later
	int _lives = 20;
	int _money = 100;
};
