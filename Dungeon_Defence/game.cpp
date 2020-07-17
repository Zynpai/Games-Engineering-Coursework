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
	//adding a square so menu isnt just a black void
	auto menuSquare = make_shared<Entity>();
	auto s = menuSquare->addComponent<ShapeComponent>();
	menuSquare->setPosition(Vector2f(600,600));
	s->setShape<RectangleShape>(Vector2f(120.0f,120.f));
	s->getShape().setFillColor(Color::Magenta);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));

	_em.list.push_back(menuSquare);
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
	//this is probably the least efficient way of doing things, but i am unsure of a different way
	std::vector<std::shared_ptr<Entity>> playerBullets;
	std::vector<std::shared_ptr<BulletMovementComponent>> BulletComponents;
	for (int i = 0; i < 5; i++) {
		auto bullet = make_shared<Entity>();
		auto s = bullet->addComponent<ShapeComponent>();
		auto a = bullet->addComponent<BulletMovementComponent>();
		s->setShape<CircleShape>(8.0f);
		s->getShape().setFillColor(Color::Blue);
		s->getShape().setOrigin(Vector2f(8.0f, 8.0f));
		a->setSpeed(300);
		//temporary damage val, can be changed for balance later
		a->damage = 20;
		bullet->setPosition(Vector2f(-50.0f,-50.0f));
		bullet->setAlive(false);
		bullet->setVisible(false);
		_em.list.push_back(bullet);
		playerBullets.push_back(bullet);
		BulletComponents.push_back(a);
	}
	

	auto player = make_shared<Entity>();
	auto s = player->addComponent<ShapeComponent>();
	auto a = player->addComponent<PlayerMovementComponent>();
	s->setShape<CircleShape>(12.f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));
	a->move(600, 400);
	a->Bulletlist = playerBullets;
	a->Componentlist = BulletComponents;

	a->Tremor = make_shared<Entity>();
	a->Tremor->setPosition(Vector2f(-50.0f, -50.0f));
	//an abombination, but a needed one (afaik)
	auto b = a->Tremor->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
	b->getShape().setFillColor(Color::Red);

	a->Wall = make_shared<Entity>();
	a->Wall->setPosition(Vector2f(-50.0f,-50.0f));
	auto c = a->Wall->addComponent<ShapeComponent>();
	c->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
	c->getShape().setFillColor(Color::Green);

	_em.list.push_back(player);
	_em.list.push_back(a->Tremor);
	_em.list.push_back(a->Wall);

}