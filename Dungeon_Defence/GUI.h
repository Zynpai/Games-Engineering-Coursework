// holds cash, lives, and deals with text
#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
//#include "cmp_player_movement.h"
using namespace std;

class GUI {
public:
	GUI();
	sf::Font font;
	static sf::Text money;
	static sf::Text lives;
	static sf::Text waveTime;

	static sf::Text Basic;
	static sf::Text Fire;
	static sf::Text Lightning;

	void setMoney(int money);
	int getMoney();
	float Buttoncooldown = 0.1;
	////used for button functionality
	//shared_ptr<PlayerMovementComponent> player;

	shared_ptr<Entity> Basicbutton;
	shared_ptr<Entity> Fireballbutton;
	shared_ptr<Entity> Lightningbutton;
	//the turret ghost that tells you where the turret will go
	shared_ptr<Entity> Ghost;

	void setLives(int lives);
	int getLives();

	void updateTimer(int Time);

	void update(double dt);

	static void Render(sf::RenderWindow &window);

protected:
	//starter values, can be changed later
	int _lives = 20;
	int _money = 100;
};
