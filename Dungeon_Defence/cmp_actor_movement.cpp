#include "cmp_actor_movement.h"
#include <LevelSystem.h>

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
}



CreepMovementComponent::CreepMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void CreepMovementComponent::update(double dt) {

}