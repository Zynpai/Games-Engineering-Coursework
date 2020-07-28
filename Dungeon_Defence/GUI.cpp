//cpp to implement gui
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "GUI.h"

using namespace sf;
using namespace std;

sf::Text GUI::money;
sf::Text GUI::lives;
sf::Text GUI::waveTime;

GUI::GUI() {
	if (!font.loadFromFile("res/arial.ttf")) {
		//it broke
		throw string("Could not load font file :(");
	}
	money.setFont(font);
	money.setString("Money: $ 100");
	money.setCharacterSize(36);
	money.setFillColor(Color::Yellow);
	money.setPosition(1530, 20);
	money.setOutlineColor(Color::Black);
	money.setOutlineThickness(1);

	lives.setCharacterSize(36);
	lives.setFont(font);
	lives.setString("Lives: 20");
	lives.setFillColor(Color::Red);
	lives.setPosition(1530, 60);
	lives.setOutlineColor(Color::Black);
	lives.setOutlineThickness(1);

	waveTime.setCharacterSize(34);
	waveTime.setFont(font);
	waveTime.setString("Time until next wave: 60s");
	waveTime.setFillColor(Color::Blue);
	waveTime.setPosition(1530, 1000);
	waveTime.setOutlineColor(Color::Black);
	waveTime.setOutlineThickness(1);
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

void GUI::updateTimer(int Time){
	waveTime.setString("Time until next wave: "+ to_string(Time) +"s");
}

void GUI::Render(RenderWindow &window) {
	window.draw(money);
	window.draw(lives);
	window.draw(waveTime);
}