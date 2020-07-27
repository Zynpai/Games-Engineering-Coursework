// holds cash, lives, and deals with text

#include <SFML/Graphics.hpp>
#include <ecm.h>
class GUI {
public:

	sf::Font font;
	sf::Text money;
	sf::Text lives;

	void setMoney(int money);
	int getMoney();

	void setLives(int lives);
	int getLives();



protected:
	int _lives;
	int _money;
};
