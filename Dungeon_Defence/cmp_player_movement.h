#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ecm.h>
#include "cmp_actor_movement.h"
#include "turret_Controller.h"
#include "Wave_controller.h"

class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent(Entity* p);
	//i know this is bad practice but i dont have time to make a workaround right now
	std::vector<std::shared_ptr<Entity>> Bulletlist;
	std::vector<std::shared_ptr<BulletMovementComponent>> Componentlist;

	std::vector<std::shared_ptr<Entity>> Creeplist;
	std::vector<std::shared_ptr<CreepMovementComponent>> creepComponentlist;
	//stores all creeps that were hit by tremor, so that i can reset their speed
	std::vector<std::shared_ptr<CreepMovementComponent>> TremorList;


	std::shared_ptr<Entity> Wall;
	std::shared_ptr<Entity> Tremor;
	std::shared_ptr<TurretController> Tcontrol;
	std::shared_ptr<WaveController> Wcontrol;
	std::shared_ptr<GUI> gui;

	int bulletpointer = 0;
	float shotCooldown = 0.0f;
	float wallCooldown = 0.0f;
	float tremorCooldown = 0.0f;
	void update(double dt) override;
};