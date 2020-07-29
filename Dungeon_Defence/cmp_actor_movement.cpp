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
		if (sqrt(pow(target->getPosition().x - _parent->getPosition().x,2)) <= 10 && sqrt(pow((target->getPosition().y-20) - _parent->getPosition().y, 2)) <=10) {
			//insert damage scripts here
			int calcDamage = (damage - targetComponent->armor);
			if (calcDamage <= 0) {
				calcDamage = 1;
			}
			targetComponent->health = targetComponent->health - calcDamage;
			if (targetComponent->health <=0) {
				if (target->isAlive()) {
					gui->setMoney(gui->getMoney() + targetComponent->reward);
					target->setAlive(false);
					target->setVisible(false);
				}
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
				if (sqrt(pow(Creeplist.at(i)->getPosition().x - _parent->getPosition().x, 2)) <= 20 && sqrt(pow((Creeplist.at(i)->getPosition().y-20) - _parent->getPosition().y, 2)) <= 20) {
					//health goes down by damage, reduced by armor to a min of 1
					int calcDamage = (damage - CreepComponentlist.at(i)->armor);
					if (calcDamage <= 0) {
						calcDamage = 1;
					}
					CreepComponentlist.at(i)->health = CreepComponentlist.at(i)->health - calcDamage;
					if (CreepComponentlist.at(i)->health <= 0) {
						if(Creeplist.at(i)->isAlive()){
							gui->setMoney(gui->getMoney() + CreepComponentlist.at(i)->reward);
							Creeplist.at(i)->setAlive(false);
							Creeplist.at(i)->setVisible(false);
						}
					}
					_parent->setAlive(false);
					_parent->setVisible(false);

				}
			}
			

		}
	}
	
}





//for enemy use
//right, left
static const Vector2i directions[] = { Vector2i{ 1, 0 }, Vector2i{ -1, 0 } };

CreepMovementComponent::CreepMovementComponent(Entity* p): ActorMovementComponent(p) {
	_state = ROAMING;
	_speed = 1.5f;
	_direction = Vector2f(Vector2i{ 0, 1 });
}

void CreepMovementComponent::update(double dt) {
	//amount to move
	const auto mva = (float)(dt * _speed);
	//current position
	const Vector2f pos = _parent->getPosition();
	//next pos
	const Vector2f newPos = pos + _direction * mva;
	////inverse of current pos
	//const Vector2i badDir = -1 * Vector2i(_direction);
	//random new direction (left and right)
	Vector2i newDir = directions[(rand() % 2)];


	//down direction
	bool down = false;
	Vector2i downDir = Vector2i{ 0, 1 };


	switch (_state)
	{
	case CreepMovementComponent::ROAMING:
		if (ls::getTileAt(newPos) == ls::ENEMY) { //if wall in front 
			_state = ROTATING; //start rotating
		}
		else {
			move(_direction * mva); //keep moving
		}
		break;
	case CreepMovementComponent::ROTATING:
		//if down direction isnt a wall prioritise going there first
		if (ls::getTileAt(pos + Vector2f(downDir) * mva) != ls::ENEMY)
		{
			newDir = downDir;
			
		}
		else
		{
			while (ls::getTileAt(pos + Vector2f(newDir) * mva) == ls::ENEMY && newDir == oldDir) {
				oldDir = newDir;
				newDir = directions[(rand() % 2)];						
			}
		}
		oldDir = newDir;
		_direction = Vector2f(newDir);
		_state = ROTATED;
		break;
	case CreepMovementComponent::ROTATED:
		_state = ROAMING; //roam
		//move(_direction * mva); //keep moving
		break;
	}

	//ActorMovementComponent::update(dt);

	//lose lives
	if (ls::getTileAt(_parent->getPosition()) == ls::START) {
		gui->setLives(gui->getLives()-1);
		_parent->setAlive(false);
		_parent->setVisible(false);
	}
}

