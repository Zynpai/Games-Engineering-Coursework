#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "cmp_actor_movement.h"
#include "turret_Controller.h"

class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent(Entity* p);
	//i know this is bad practice but i dont have time to make a workaround right now
	std::vector<std::shared_ptr<Entity>> Bulletlist;
	std::vector<std::shared_ptr<BulletMovementComponent>> Componentlist;

	std::shared_ptr<Entity> Wall;
	std::shared_ptr<Entity> Tremor;
	std::shared_ptr<TurretController> Tcontrol;

	int bulletpointer = 0;
	float shotCooldown = 0.0f;
	float wallCooldown = 0.0f;
	float tremorCooldown = 0.0f;
	void update(double dt) override;
};