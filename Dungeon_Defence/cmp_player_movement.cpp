#include "cmp_player_movement.h"


PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::A)) {

		move(Vector2f(-_speed, 0.0f)*float(dt));

	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {

		move(Vector2f(_speed, 0.0f)*float(dt));

	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {

		move(Vector2f(0.0f, -_speed)*float(dt));

	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {

		move(Vector2f(0.0f, _speed)*float(dt));

	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		
		//Basic attack
		if (shotCooldown <= 0.0f) {
			auto bullet = Bulletlist.at(bulletpointer);
			auto a = Componentlist.at(bulletpointer);
			Vector2f MousePos = Vector2f(Mouse::getPosition());
			float magnitude = sqrt(pow(MousePos.x - _parent->getPosition().x, 2) + pow(MousePos.y - _parent->getPosition().y, 2));
			Vector2f direction = (MousePos - _parent->getPosition()) / (magnitude);
			a->VecTarget = direction;
			a->move(_parent->getPosition() - bullet->getPosition());
			bulletpointer++;
			if (bulletpointer >= 5) { bulletpointer = 0; }
			shotCooldown = 1.0f;
			bullet->setAlive(true);
			bullet->setVisible(true);
		}
		
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		//Wall ability
		if (wallCooldown <= 0.0f) {
			Wall->setPosition(Vector2f(Mouse::getPosition()));

			wallCooldown = 10.0f;
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		//Tremor ability
		if (tremorCooldown <= 0.0f) {
			Tremor->setPosition(Vector2f(Mouse::getPosition()));

			tremorCooldown = 5.0f;
		}
	}
	//hotkeys for turrets
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		Tcontrol->updateStored("basic");
		Tcontrol->placementMode = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::R)) {
		Tcontrol->updateStored("fireball");
		Tcontrol->placementMode = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::T)) {
		Tcontrol->updateStored("lightning");
		Tcontrol->placementMode = true;
	}


	//update cooldowns
	if (shotCooldown > 0.0f) {
		shotCooldown = shotCooldown - dt;
	}
	if (wallCooldown > 0.0f) {
		wallCooldown = wallCooldown - dt;
	}
	if (tremorCooldown > 0.0f) {
		tremorCooldown = tremorCooldown - dt;
	}
}
