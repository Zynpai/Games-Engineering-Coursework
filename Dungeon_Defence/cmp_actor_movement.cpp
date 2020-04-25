#include "cmp_actor_movement.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ecm.h"
#include "levelsystem.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
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
		float magnitude = sqrt(pow(VecTarget.x - _parent->getPosition().x, 2) + pow(VecTarget.y - _parent->getPosition().y, 2));
		Vector2f direction = (VecTarget - _parent->getPosition()) / (magnitude);
		move(direction*_speed*float(dt));
		//copy of above
		if (sqrt(pow(VecTarget.x - _parent->getPosition().x, 2)) <= 10 && sqrt(pow(VecTarget.y - _parent->getPosition().y, 2)) <= 10) {

			_parent->setAlive(false);
			_parent->setVisible(false);
		}
	}
	
}


PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		
		move(Vector2f(-_speed, 0.0f)*float(dt));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		
		move(Vector2f(_speed, 0.0f)*float(dt));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
	
		move(Vector2f(0.0f, -_speed)*float(dt));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
	
		move(Vector2f(0.0f, _speed)*float(dt));
		
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		//Basic attack
		if (shotCooldown <= 0.0f) {
			auto bullet = Bulletlist.at(bulletpointer);
			auto a = Componentlist.at(bulletpointer);
			bullet->setAlive(true);
			bullet->setVisible(true);
			a->VecTarget = Vector2f(Mouse::getPosition());
			a->move(_parent->getPosition() - bullet->getPosition());
			bulletpointer++;
			if (bulletpointer >= 5) { bulletpointer = 0; }
			shotCooldown = 1.0f;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		//Wall ability
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		//Tremor ability
	}

	//update cooldowns
	if (shotCooldown > 0.0f) {
		shotCooldown = shotCooldown - dt;
	}
}





CreepMovementComponent::CreepMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void CreepMovementComponent::update(double dt) {

}

