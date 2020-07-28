#pragma once
#include "cmp_actor_movement.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "scene.h"
#include "game.h"
#include <LevelSystem.h>
#include "GUI.h"

using namespace std;
using namespace sf;


void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(200.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}


void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

void ActorMovementComponent::Uncheckedmove(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;

	_parent->setPosition(pp);
	
}


void ActorMovementComponent::Uncheckedmove(float x, float y) {
	move(Vector2f(x, y));
}


float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }


BulletMovementComponent::BulletMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void BulletMovementComponent::update(double dt) {
	if (targeted) {
		float magnitude = sqrt(pow(target->getPosition().x - _parent->getPosition().x, 2) + pow(target->getPosition().y - _parent->getPosition().y, 2));
		Vector2f direction = (target->getPosition() - _parent->getPosition()) / (magnitude);
		move(direction*_speed*float(dt));
		//if the distance between the bullet and target is low enough, terminate the bullet and damage the target
		//pow and sqrt to get a positive distance, actual distance number is placeholder
		if (sqrt(pow(target->getPosition().x - _parent->getPosition().x,2)) <= 10 && sqrt(pow(target->getPosition().y - _parent->getPosition().y, 2)) <=10) {
			//insert damage scripts here
			targetComponent->health = targetComponent->health - damage;
			if (targetComponent->health <=0) {
				gui->setMoney(gui->getMoney() + targetComponent->reward);
				target->setAlive(false);
				target->setVisible(false);
			}
			_parent->setAlive(false);
			_parent->setVisible(false);
		}
	}
	else {
		
		Uncheckedmove(VecTarget*_speed*float(dt));
		//if out of bounds of screen, delete
		VideoMode desktop = VideoMode::getDesktopMode();

		float gameHeight = desktop.height;
		float gameWidth = desktop.width;

		if (_parent->getPosition().x <= 0 || _parent->getPosition().y <= 0 || _parent->getPosition().x >= gameWidth || _parent->getPosition().y >= gameHeight) {
			_parent->setAlive(false);
			_parent->setVisible(false);
		}
		//if it collides with an enemy, do damage and disapear
		for (int i = 0; i < Creeplist.size(); i++) {
			if (Creeplist.at(i)->isAlive()) {
				if (sqrt(pow(Creeplist.at(i)->getPosition().x - _parent->getPosition().x, 2)) <= 20 && sqrt(pow(Creeplist.at(i)->getPosition().y - _parent->getPosition().y, 2)) <= 20) {

					CreepComponentlist.at(i)->health = CreepComponentlist.at(i)->health - damage;
					if (CreepComponentlist.at(i)->health <= 0) {
						gui->setMoney(gui->getMoney() + CreepComponentlist.at(i)->reward);
						Creeplist.at(i)->setAlive(false);
						Creeplist.at(i)->setVisible(false);
					}
					_parent->setAlive(false);
					_parent->setVisible(false);

				}
			}
			

		}
	}
	
}





//for enemy use

CreepMovementComponent::CreepMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void CreepMovementComponent::update(double dt) {
	//just some code to make sure spacing works, delete when real code is used
	move(0, 1.5);
	if (ls::getTileAt(_parent->getPosition()) == ls::START) {
		gui->setLives(gui->getLives()-1);
		_parent->setAlive(false);
		_parent->setVisible(false);
	}
}

