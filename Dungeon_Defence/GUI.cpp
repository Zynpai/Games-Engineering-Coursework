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

sf::Text GUI::Towers;
sf::Text GUI::Abilities;

sf::Text GUI::tremorCooldown;
sf::Text GUI::wallCooldown;

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
	Basic.setPosition(1630, 160);
	Basic.setOutlineColor(Color::Black);
	Basic.setOutlineThickness(1);

	Fire.setCharacterSize(25);
	Fire.setFont(font);
	Fire.setString("Fireball   $50 (R)");
	Fire.setFillColor(Color::Yellow);
	Fire.setPosition(1630, 310);
	Fire.setOutlineColor(Color::Black);
	Fire.setOutlineThickness(1);

	Lightning.setCharacterSize(25);
	Lightning.setFont(font);
	Lightning.setString("Lightning   $40 (T)");
	Lightning.setFillColor(Color::Yellow);
	Lightning.setPosition(1630, 460);
	Lightning.setOutlineColor(Color::Black);
	Lightning.setOutlineThickness(1);

	Towers.setCharacterSize(35);
	Towers.setFont(font);
	Towers.setString("TOWERS");
	Towers.setFillColor(Color::Black);
	Towers.setPosition(1630, 110);

	Abilities.setCharacterSize(35);
	Abilities.setFont(font);
	Abilities.setString("ABILITES");
	Abilities.setFillColor(Color::Black);
	Abilities.setPosition(1630, 860);

	tremorCooldown.setCharacterSize(25);
	tremorCooldown.setFont(font);
	tremorCooldown.setString("Tremor (2): 0s");
	tremorCooldown.setFillColor(Color::Green);
	tremorCooldown.setPosition(1630, 940);
	tremorCooldown.setOutlineColor(Color::Black);
	tremorCooldown.setOutlineThickness(1);

	wallCooldown.setCharacterSize(25);
	wallCooldown.setFont(font);
	wallCooldown.setString("Earth Wall (1): 0s");
	wallCooldown.setFillColor(Color::Green);
	wallCooldown.setPosition(1630, 910);
	wallCooldown.setOutlineColor(Color::Black);
	wallCooldown.setOutlineThickness(1);
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
void GUI::updateWall(int Time) {
	
	if (time == 0) {
		wallCooldown.setFillColor(Color::Green);
	}
	else {
		wallCooldown.setFillColor(Color::Yellow);
	}
	wallCooldown.setString("Earth Wall (1): " + to_string(Time) + "s");
}
void GUI::updateTremor(int Time) {
	
	if (time == 0) {
		tremorCooldown.setFillColor(Color::Green);
	}
	else {
		tremorCooldown.setFillColor(Color::Yellow);
	}
	tremorCooldown.setString("Tremor (2): " + to_string(Time) + "s");
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
	window.draw(Towers);
	window.draw(Abilities);
	window.draw(tremorCooldown);
	window.draw(wallCooldown);
}