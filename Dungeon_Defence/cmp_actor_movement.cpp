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
	//if (validMove(pp)) {
		_parent->setPosition(pp);
	//}
}


void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }


BulletMovementComponent::BulletMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void BulletMovementComponent::update(double dt) {
	if (targeted) {
		float magnitude = sqrt(pow(target.getPosition().x - _parent->getPosition().x, 2) + pow(target.getPosition().y - _parent->getPosition().y, 2));
		Vector2f direction = (target.getPosition() - _parent->getPosition()) / (magnitude);
		move(direction*_speed*float(dt));
		//if the distance between the bullet and target is low enough, terminate the bullet and damage the target
		//pow and sqrt to get a positive distance, actual distance number is placeholder
		if (sqrt(pow(target.getPosition().x - _parent->getPosition().x,2)) <= 10 && sqrt(pow(target.getPosition().y - _parent->getPosition().y, 2)) <=10) {
			//insert damage scripts here
			_parent->setAlive(false);
			_parent->setVisible(false);
		}
	}
	else {
		
		move(VecTarget*_speed*float(dt));
		//if out of bounds of screen, delete
		VideoMode desktop = VideoMode::getDesktopMode();

		float gameHeight = desktop.height;
		float gameWidth = desktop.width;

		if (_parent->getPosition().x <= 0 || _parent->getPosition().y <= 0 || _parent->getPosition().x >= gameWidth || _parent->getPosition().y >= gameHeight) {
			_parent->setAlive(false);
			_parent->setVisible(false);
		}
		//if it collides with an enemy, do damage and disapear

	}
	
}





//for enemy use

CreepMovementComponent::CreepMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void CreepMovementComponent::update(double dt) {

}

