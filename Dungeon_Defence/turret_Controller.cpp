// a shell built to handle all turret related transactions, including telling the turret what type it is and giving it its stats, store the prebuilt turrets, and alert the player when they reach the limit
#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "system_renderer.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_turret.h"
#include "turret_Controller.h"

using namespace std;
using namespace sf;

TurretController::TurretController() {}

void TurretController::Placeturret(string type) {
	//only place a turret if you havent hit the limit yet, can adjust limit later
	if (cooldown == 0.0f) {
		if (turretpointer < 30) {
			if (type == "basic") {
				auto turret = Turretlist.at(turretpointer);
				if (ls::getTileAt(Vector2f(Mouse::getPosition())) == ls::ENEMY) {
					//center turret on tile
					int xcomponent = ((floor(Mouse::getPosition().x / 80)) * 80) + 40;
					int ycomponent = ((floor(Mouse::getPosition().y / 80)) * 80) + 40;
					Vector2f Tile = Vector2f(xcomponent, ycomponent);
					turret->setPosition(Tile);
					turret->setAlive(true);
					turret->setVisible(true);

					auto tcomp = Componentlist.at(turretpointer);
					tcomp->setDamage(1);
					tcomp->setRate(1);
					tcomp->setRange(200);
					tcomp->targetAir = true;
					tcomp->targetGround = true;
					//charge player for price of turret


					turretpointer++;
				}
				

			}

		}
		cooldown = 0.2f;
	}
}


void TurretController::update(double dt) {
	if (cooldown > 0.0f) {
		cooldown = cooldown - dt;
		if (cooldown < 0.0f) {
			cooldown = 0.0f;
		}

	}
}



