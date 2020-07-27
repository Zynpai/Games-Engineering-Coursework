//cpp to implement gui
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "GUI.h"


GUI::GUI () {}


int GUI::getLives() {
	return _lives;
}
void GUI::setLives(int live) {
	_lives = live;
	lives.setString("Lives: "+ _lives);
}
int GUI::getMoney() {
	return _money;
}
void GUI::setMoney(int cash) {
	_money = cash;
	money.setString("Money: $ " + _money);
}