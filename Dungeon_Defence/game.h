#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> endScene;
extern std::shared_ptr<Scene> activeScene;


class MenuScene : public Scene {
private:

public:
	sf::Texture Menu;
	sf::Sprite sMenu;
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

class EndScene : public Scene {
private:

public:
	sf::Text text;
	sf::Font font;
	sf::Texture End;
	sf::Sprite sEnd;
	EndScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};


class GameScene : public Scene {
private:
	void respawn();

public:
	sf::Texture map;
	sf::Sprite sMap;
	//sf::Texture footman ;
	//sf::Texture sfootman;
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};