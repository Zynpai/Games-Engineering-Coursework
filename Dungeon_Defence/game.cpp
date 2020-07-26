#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "scene.h"
#include "game.h"
#include "cmp_turret.h"
#include "turret_controller.h"
#include "cmp_player_movement.h"
#include "Wave_controller.h"

using namespace sf;
using namespace std;

//global so i can put it in gamescene's update
auto tControl = make_shared<TurretController>();
auto wControl = make_shared<WaveController>();

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

	tControl->update(dt);
	wControl->update(dt);
}

void GameScene::render() {
	ls::Render(Renderer::getWindow());
	Scene::render();
}

void GameScene::load() {
	//this is probably the least efficient way of doing things, but i am unsure of a different way
	//targetlist stores a smaller list of entities for turrets, to save on processing time (aka zy when you make creeps put them here)
	std::vector<std::shared_ptr<Entity>> TargetList;
	std::vector<std::shared_ptr<Entity>> playerBullets;
	std::vector<std::shared_ptr<BulletMovementComponent>> BulletComponents;
	for (int i = 0; i < 5; i++) {
		auto bullet = make_shared<Entity>();
		auto s = bullet->addComponent<ShapeComponent>();
		auto a = bullet->addComponent<BulletMovementComponent>();
		s->setShape<CircleShape>(8.0f);
		s->getShape().setFillColor(Color::Blue);
		s->getShape().setOrigin(Vector2f(4.0f, 4.0f));
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
	s->getShape().setOrigin(Vector2f(6.f, 6.f));
	player->setPosition(Vector2f(600, 400));
	a->Bulletlist = playerBullets;
	a->Componentlist = BulletComponents;
	

	a->Tremor = make_shared<Entity>();
	a->Tremor->setPosition(Vector2f(-50.0f, -50.0f));
	//an abombination, but a needed one (afaik)
	auto b = a->Tremor->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
	b->getShape().setOrigin(Vector2f(25.0f, 25.0f));
	b->getShape().setFillColor(Color::Red);

	a->Wall = make_shared<Entity>();
	a->Wall->setPosition(Vector2f(-50.0f,-50.0f));
	auto c = a->Wall->addComponent<ShapeComponent>();
	c->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
	c->getShape().setOrigin(Vector2f(25.0f, 25.0f));
	c->getShape().setFillColor(Color::Green);

	_em.list.push_back(player);
	//testing turrets fire capabilites with player first
	//TargetList.push_back(player);
	_em.list.push_back(a->Tremor);
	_em.list.push_back(a->Wall);


	//now to make a list of reusable creeps, 20 should suffice
	for (int l = 0; l < 20; l++) {
		auto creep = make_shared<Entity>();
		auto s = creep->addComponent<ShapeComponent>();
		auto m = creep->addComponent<CreepMovementComponent>();

		s->setShape<CircleShape>(12.0f);
		s->getShape().setOrigin(Vector2f(6.0f,6.0f));
		s->getShape().setFillColor(Color::Magenta);

		creep->setAlive(false);
		creep->setVisible(false);

		_em.list.push_back(creep);
		TargetList.push_back(creep);
		wControl->Creeplist.push_back(creep);
		wControl->Componentlist.push_back(m);
	}




	//time to settup a list of turrets to call appon, each with their own list of bullets.... yeah this is gonna be messy
	//turret limit of 30, can be changed if needed
	for (int j = 0; j < 30; j++) {
		//hurray for more inefficiency!
		std::vector<std::shared_ptr<Entity>> turretBullets;
		std::vector<std::shared_ptr<BulletMovementComponent>> turretBulletComponents;
		//each turret has 3 bullets to call uppon, shouldnt need more than this unless its long range/ rapid fire? (even then just make the bullets faster)
		for (int k = 0; k < 3; k++) {
			auto bullet = make_shared<Entity>();
			auto s = bullet->addComponent<ShapeComponent>();
			auto a = bullet->addComponent<BulletMovementComponent>();
			s->setShape<CircleShape>(8.0f);
			s->getShape().setFillColor(Color::Cyan);
			s->getShape().setOrigin(Vector2f(4.0f, 4.0f));
			a->setSpeed(1000.0f);
		
			bullet->setPosition(Vector2f(-50.0f, -50.0f));
			bullet->setAlive(false);
			bullet->setVisible(false);
			_em.list.push_back(bullet);
			turretBullets.push_back(bullet);
			turretBulletComponents.push_back(a);
		
		
		}
		auto turret = make_shared<Entity>();
		auto x = turret->addComponent<ShapeComponent>();
		auto b = turret->addComponent<TurretComponent>();
		turret->setAlive(false);
		turret->setVisible(false);

		x->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
		x->getShape().setFillColor(Color::Blue);
		x->getShape().setOrigin(Vector2f(25.0f, 25.0f));

		b->Bulletlist = turretBullets;
		b->Componentlist = turretBulletComponents;
		b->Targetlist = TargetList;
		tControl->Turretlist.push_back(turret);
		tControl->Componentlist.push_back(b);
		_em.list.push_back(turret);
	}

	a->Tcontrol = tControl;

	ls::loadLevelFile("res/levels/maze_3.txt", 80.0f);
}