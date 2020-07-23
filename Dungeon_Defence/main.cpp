#pragma once
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
	VideoMode desktop = VideoMode::getDesktopMode();
	//now it can run at any resolution in fullscreen (saves me trying to figure out the relative mouse possitions for aiming

	float gameHeight = desktop.height;
	float gameWidth = desktop.width;
	
	RenderWindow window(VideoMode(gameWidth, gameHeight, desktop.bitsPerPixel), "Dungeon Defence" , Style::Fullscreen);
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
