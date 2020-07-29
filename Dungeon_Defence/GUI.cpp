//cpp to implement gui
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "GUI.h"
#include "levelsystem.h"
using namespace sf;
using namespace std;

sf::Text GUI::money;
sf::Text GUI::lives;
sf::Text GUI::waveTime;

sf::Text GUI::Basic;
sf::Text GUI::Fire;
sf::Text GUI::Lightning;

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

	Basic.setCharacterSize(25);
	Basic.setFont(font);
	Basic.setString("Archer   $20 (E)");
	Basic.setFillColor(Color::Yellow);
	Basic.setPosition(1630, 110);
	Basic.setOutlineColor(Color::Black);
	Basic.setOutlineThickness(1);

	Fire.setCharacterSize(25);
	Fire.setFont(font);
	Fire.setString("Fireball   $50 (R)");
	Fire.setFillColor(Color::Yellow);
	Fire.setPosition(1630, 260);
	Fire.setOutlineColor(Color::Black);
	Fire.setOutlineThickness(1);

	Lightning.setCharacterSize(25);
	Lightning.setFont(font);
	Lightning.setString("Lightning   $40 (T)");
	Lightning.setFillColor(Color::Yellow);
	Lightning.setPosition(1630, 410);
	Lightning.setOutlineColor(Color::Black);
	Lightning.setOutlineThickness(1);
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

void GUI::update(double dt) {
	//basic ui design, if you have enough to buy the tower, light up green
	if (_money >= 20) {
		Basic.setFillColor(Color::Green);
	}
	else {
		Basic.setFillColor(Color::Yellow);
	}

	if (_money >= 50) {
		Fire.setFillColor(Color::Green);
	}
	else {
		Fire.setFillColor(Color::Yellow);
	}

	if (_money >= 40) {
		Lightning.setFillColor(Color::Green);
	}
	else {
		Lightning.setFillColor(Color::Yellow);
	}



}

void GUI::Render(RenderWindow &window) {
	window.draw(money);
	window.draw(lives);
	window.draw(waveTime);
	window.draw(Basic);
	window.draw(Fire);
	window.draw(Lightning);
}