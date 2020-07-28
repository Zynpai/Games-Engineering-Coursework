//cpp to implement gui
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "GUI.h"

using namespace sf;
using namespace std;

sf::Text GUI::money;
sf::Text GUI::lives;

GUI::GUI() {
	if (!font.loadFromFile("res/arial.ttf")) {
		//it broke
		throw string("Could not load font file :(");
	}
	money.setFont(font);
	lives.setFont(font);
	lives.setString("Lives: 20");
	money.setString("Money: $ 100");
	money.setCharacterSize(30);
	lives.setCharacterSize(30);
	money.setFillColor(Color::Yellow);
	lives.setFillColor(Color::Red);
	money.setPosition(1550, 20);
	lives.setPosition(1550, 50);
	money.setOutlineColor(Color::Black);
	lives.setOutlineColor(Color::Black);
	money.setOutlineThickness(1);
	lives.setOutlineThickness(1);
}


int GUI::getLives() {
	return _lives;
}
void GUI::setLives(int live) {
	_lives = live;
	lives.setString("Lives: "+ to_string(_lives));
	if (_lives <=0) {
		//game over
	}
}
int GUI::getMoney() {
	return _money;
}
void GUI::setMoney(int cash) {
	_money = cash;
	money.setString("Money: $ " + to_string(_money));
}

void GUI::Render(RenderWindow &window) {
	window.draw(money);
	window.draw(lives);
}