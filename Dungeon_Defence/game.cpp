#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "scene.h"
#include "game.h"

using namespace sf;
using namespace std;

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	Scene::update(dt);

}

void MenuScene::render() {
	Scene::render();
}

void MenuScene::load() {

}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::load() {
	auto player = make_shared<Entity>();
	auto s = player->addComponent<ShapeComponent>();
	auto a = player->addComponent<PlayerMovementComponent>();
	s->setShape<CircleShape>(12.f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));
	a->move(600, 400);
	_em.list.push_back(player);
}