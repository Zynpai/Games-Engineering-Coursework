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
#include "GUI.h"

using namespace sf;
using namespace std;

//global so i can put it in gamescene's update
auto tControl = make_shared<TurretController>();
auto wControl = make_shared<WaveController>();
auto gameGUI = make_shared<GUI>();



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
	gameGUI->update(dt);
}

void GameScene::render() {
	//ls::Render(Renderer::getWindow());
	Scene::render();

	Renderer::getWindow().draw(sMap);
	gameGUI->Render(Renderer::getWindow());
}


void GameScene::load() {
	//sf::Texture map;
	map.loadFromFile("res/Map2.png");

	// Create a sprite
	//sf::Sprite sprite;
	sMap.setTexture(map);
	sMap.setPosition(0, 0);

	tControl->gui = gameGUI;
	wControl->gui = gameGUI;
	//initialise buttons and ghost for gui
	auto Basicbutton = make_shared<Entity>();
	auto sh = Basicbutton->addComponent<ShapeComponent>();
	sh->setShape<RectangleShape>(Vector2f(200,100));
	sh->getShape().setFillColor(Color::Black);
	sh->getShape().setOrigin(Vector2f(100,50));
	Basicbutton->setPosition(Vector2f(1730, 250));
	_em.list.push_back(Basicbutton);
	tControl->Basicbutton = Basicbutton;

	auto Fireballbutton = make_shared<Entity>();
	auto sh2 = Fireballbutton->addComponent<ShapeComponent>();
	sh2->setShape<RectangleShape>(Vector2f(200, 100));
	sh2->getShape().setFillColor(Color::Black);
	sh2->getShape().setOrigin(Vector2f(100, 50));
	Fireballbutton->setPosition(Vector2f(1730, 400));
	_em.list.push_back(Fireballbutton);
	tControl->Fireballbutton = Fireballbutton;

	auto Lightningbutton = make_shared<Entity>();
	auto sh3 = Lightningbutton->addComponent<ShapeComponent>();
	sh3->setShape<RectangleShape>(Vector2f(200, 100));
	sh3->getShape().setFillColor(Color::Black);
	sh3->getShape().setOrigin(Vector2f(100, 50));
	Lightningbutton->setPosition(Vector2f(1730, 550));
	_em.list.push_back(Lightningbutton);
	tControl->Lightningbutton = Lightningbutton;

	//ghost is the only one that should keep a shape, sprites would be preffered for buttons
	auto Ghost = make_shared<Entity>();
	auto sh4 = Ghost->addComponent<ShapeComponent>();
	sh4->setShape<RectangleShape>(Vector2f(50, 50));
	Color transparent_grey(30,30,30,150);
	sh4->getShape().setFillColor(transparent_grey);
	sh4->getShape().setOrigin(Vector2f(25, 25));
	_em.list.push_back(Ghost);
	Ghost->setAlive(false);
	Ghost->setVisible(false);
	tControl->Ghost = Ghost;
	tControl->GhostComponent = sh4;

	auto RGhost = make_shared<Entity>();
	auto sh5 = RGhost->addComponent<ShapeComponent>();
	_em.list.push_back(RGhost);
	RGhost->setAlive(false);
	RGhost->setVisible(false);
	tControl->RGhost = RGhost;
	tControl->RGhostComponent = sh5;

	std::vector<std::shared_ptr<Entity>> TargetList;
	//now to make a list of reusable creeps, 20 should suffice
	for (int l = 0; l < 20; l++) {
		auto creep = make_shared<Entity>();
		auto s = creep->addComponent<ShapeComponent>();
		auto m = creep->addComponent<CreepMovementComponent>();

		s->setShape<CircleShape>(20.0f);
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(Vector2f(20.0f,40.0f));
		//footman.loadFromFile("res/Map2.png");
		//s->sprite->setTexture(blankTex);
		

		creep->setAlive(false);
		creep->setVisible(false);
		m->gui = gameGUI;

		_em.list.push_back(creep);
		TargetList.push_back(creep);
		wControl->Creeplist.push_back(creep);
		wControl->Componentlist.push_back(m);
		//wControl->spriteList.push_back(s);

	}

	//this is probably the least efficient way of doing things, but i am unsure of a different way
	//targetlist stores a smaller list of entities for turrets, to save on processing time
	std::vector<std::shared_ptr<Entity>> playerBullets;
	std::vector<std::shared_ptr<BulletMovementComponent>> BulletComponents;
	for (int i = 0; i < 5; i++) {
		auto bullet = make_shared<Entity>();
		auto s = bullet->addComponent<ShapeComponent>();
		auto a = bullet->addComponent<BulletMovementComponent>();
		s->setShape<CircleShape>(8.0f);
		s->getShape().setFillColor(Color::Cyan);
		s->getShape().setOrigin(Vector2f(4.0f, 4.0f));
		a->setSpeed(300);
		a->gui = gameGUI;
		a->Creeplist = wControl->Creeplist;
		a->CreepComponentlist = wControl->Componentlist;
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
	//for tremor ability
	a->Creeplist = wControl->Creeplist;
	a->creepComponentlist = wControl->Componentlist;
	a->gui = gameGUI;

	a->Tremor = make_shared<Entity>();
	a->Tremor->setPosition(Vector2f(-50.0f, -50.0f));
	//an abombination, but a needed one (afaik)
	auto b = a->Tremor->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(200.0f, 200.0f));
	b->getShape().setOrigin(Vector2f(100.0f, 100.0f));
	a->Tremor->setAlive(false);
	a->Tremor->setVisible(false);
	Color transparent_red(200, 0, 0, 150);
	b->getShape().setFillColor(transparent_red);


	a->Wall = make_shared<Entity>();
	a->Wall->setPosition(Vector2f(-50.0f,-50.0f));
	auto c = a->Wall->addComponent<ShapeComponent>();
	c->setShape<RectangleShape>(Vector2f(50.0f, 50.0f));
	c->getShape().setOrigin(Vector2f(25.0f, 25.0f));
	c->getShape().setFillColor(Color::Green);

	_em.list.push_back(player);
	_em.list.push_back(a->Tremor);
	_em.list.push_back(a->Wall);


	




	//time to settup a list of turrets to call appon, each with their own list of bullets.... yeah this is gonna be messy
	//turret limit of 30, can be changed if needed
	for (int j = 0; j < 50; j++) {
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
			a->gui = gameGUI;
		
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
		x->getShape().setFillColor(Color::Green);
		x->getShape().setOrigin(Vector2f(25.0f, 25.0f));

		b->Bulletlist = turretBullets;
		b->Componentlist = turretBulletComponents;
		b->Targetlist = TargetList;
		b->creepComponentlist = wControl->Componentlist;
		tControl->Turretlist.push_back(turret);
		tControl->Componentlist.push_back(b);
		_em.list.push_back(turret);
	}

	a->Tcontrol = tControl;

	ls::loadLevelFile("res/levels/maze_3.txt", 80.0f);
}