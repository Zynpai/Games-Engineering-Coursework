#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "scene.h"
#include "game.h"

using namespace sf;
using namespace std;

float gameHeight = 800.0f;
float gameWidth = 1200.0f;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

void load(RenderWindow &window) {
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	activeScene = menuScene;
	Renderer::initialise(window);
}

void reset() {
}

void update(RenderWindow &window) {

	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	activeScene->update(dt);
}

void render(RenderWindow &window) {
	activeScene->render();
	Renderer::render();
}




int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Dungeon Defence");
	load(window);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) {
		window.clear();
		update(window);
		render(window);
		window.display();
	}


	return 0;
}
