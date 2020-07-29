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

TurretController::TurretController() {
	grey.r = 30;
	grey.g = 30;
	grey.b = 30;
	grey.a = 150;

	red.r = 200;
	red.g = 0;
	red.b = 0;
	red.a = 150;

}

void TurretController::Placeturret(string type) {
	//only place a turret if you havent hit the limit yet, can adjust limit later
	if (cooldown == 0.0f) {
		if (ls::getTileAt(Vector2f(Mouse::getPosition())) == ls::ENEMY) {
			//center turret on tile
			int xcomponent = ((floor(Mouse::getPosition().x / 80)) * 80) + 40;
			int ycomponent = ((floor(Mouse::getPosition().y / 80)) * 80) + 40;
			Vector2f Tile = Vector2f(xcomponent, ycomponent);
			bool valid = true;
			for (int i = 0; i < Occupied.size(); i++) {
				if (Occupied.at(i) == Tile) {
					valid = false;
				}
			}
			if (valid) {
				Occupied.push_back(Tile);
				if (turretpointer < 30) {
					if (type == "basic") {
						//basic cost of 20, can be ballanced later
						if (gui->getMoney()>= 20) {
							gui->setMoney(gui->getMoney()-20);
							auto turret = Turretlist.at(turretpointer);


							turret->setPosition(Tile);
							turret->setAlive(true);
							turret->setVisible(true);

							auto tcomp = Componentlist.at(turretpointer);
							tcomp->setDamage(5);
							tcomp->setRate(1);
							tcomp->setRange(200);
							tcomp->targetAir = true;
							tcomp->targetGround = true;
							


							turretpointer++;
						}
						
					}
					if (type == "fireball") {
						//fireball cost of 50, can be ballanced later
						if (gui->getMoney() >= 50) {
							gui->setMoney(gui->getMoney() - 50);
							auto turret = Turretlist.at(turretpointer);


							turret->setPosition(Tile);
							turret->setAlive(true);
							turret->setVisible(true);

							auto tcomp = Componentlist.at(turretpointer);
							tcomp->setDamage(40);
							tcomp->setRate(3);
							tcomp->setRange(300);
							tcomp->targetAir = false;
							tcomp->targetGround = true;
							


							turretpointer++;
						}
					}
					if (type == "lightning") {
						//lightning cost of 40, can be ballanced later
						if (gui->getMoney() >= 40) {
							gui->setMoney(gui->getMoney() - 40);
							auto turret = Turretlist.at(turretpointer);


							turret->setPosition(Tile);
							turret->setAlive(true);
							turret->setVisible(true);

							auto tcomp = Componentlist.at(turretpointer);
							tcomp->setDamage(30);
							tcomp->setRate(2);
							tcomp->setRange(500);
							tcomp->targetAir = true;
							tcomp->targetGround = false;
								


							turretpointer++;
						}
					}
					

				}
			}
			

		}
		cooldown = 0.05f;
	}
}

void TurretController::updateStored(string turret) {
	storedTurret = turret;
	if(storedTurret == "basic") {
		RGhostComponent->setShape<CircleShape>(200);
		RGhostComponent->getShape().setOrigin(Vector2f(200, 200));
		RGhostComponent->getShape().setFillColor(grey);
	}
	else if (storedTurret == "fireball") {
		RGhostComponent->setShape<CircleShape>(300);
		RGhostComponent->getShape().setOrigin(Vector2f(300, 300));
		RGhostComponent->getShape().setFillColor(grey);
	}
	else if (storedTurret == "lightning") {
		RGhostComponent->setShape<CircleShape>(500);
		RGhostComponent->getShape().setOrigin(Vector2f(500, 500));
		RGhostComponent->getShape().setFillColor(grey);
	}
}

void TurretController::update(double dt) {
	if (cooldown > 0.0f) {
		cooldown = cooldown - dt;
		if (cooldown < 0.0f) {
			cooldown = 0.0f;
		}

	}
	if (placementMode) {

		Ghost->setAlive(true);
		Ghost->setVisible(true);
		RGhost->setAlive(true);
		RGhost->setVisible(true);
		int xcomponent = ((floor(Mouse::getPosition().x / 80)) * 80) + 40;
		int ycomponent = ((floor(Mouse::getPosition().y / 80)) * 80) + 40;
		Vector2f Tile = Vector2f(xcomponent, ycomponent);
	
		//put the ghost hovering over the nearest tile
		Ghost->setPosition(Tile);
		RGhost->setPosition(Tile);
		//depending on if the placement is valid, change the color of the ghost accordingly
			if (ls::getTileAt(Tile) != ls::ENEMY) {
				GhostComponent->getShape().setFillColor(red);
			}
			else {
				bool valid = true;
				for (int i = 0; i < Occupied.size(); i++) {
					if (Occupied.at(i) == Tile) {
						valid = false;
					}
				}
				if (valid) {
					GhostComponent->getShape().setFillColor(grey);
				}
				else {
					GhostComponent->getShape().setFillColor(red);
				}
			}
	}

	//buttons for turrets
	if (Mouse::isButtonPressed(Mouse::Left)) {
		//if currently placing a turret, ignore the buttons
		if (placementMode) {
			//handle placements for turrets
			//dont immidiatly check for placement, or it will instantly fail
			if (Buttoncooldown <= 0) {
				Placeturret(storedTurret);
				Ghost->setAlive(false);
				Ghost->setVisible(false);
				RGhost->setAlive(false);
				RGhost->setVisible(false);
				placementMode = false;
			}
			
		}
		else {


			//check if it clicked a button
			if (sqrt(pow(Mouse::getPosition().x - Basicbutton->getPosition().x, 2)) <= 100 && sqrt(pow(Mouse::getPosition().y - Basicbutton->getPosition().y, 2)) <= 50) {
				//do something with basic turret
				if (Buttoncooldown <= 0) {
					storedTurret = "basic";
					placementMode = true;
					Buttoncooldown = 0.2f;
				}

			}
			else if (sqrt(pow(Mouse::getPosition().x - Fireballbutton->getPosition().x, 2)) <= 100 && sqrt(pow(Mouse::getPosition().y - Fireballbutton->getPosition().y, 2)) <= 50) {
				//do something with fire turret
				if (Buttoncooldown <= 0) {
					storedTurret = "fireball";
					placementMode = true;
					Buttoncooldown = 0.2f;
				}
			}
			else if (sqrt(pow(Mouse::getPosition().x - Lightningbutton->getPosition().x, 2)) <= 100 && sqrt(pow(Mouse::getPosition().y - Lightningbutton->getPosition().y, 2)) <= 50) {
				//do something with lightning turret
				if (Buttoncooldown <= 0) {
					storedTurret = "lightning";
					placementMode = true;
					Buttoncooldown = 0.2f;
				}
			}

		}
	
	}

	if (Buttoncooldown > 0) {

		Buttoncooldown = Buttoncooldown - dt;
	}
	if (Buttoncooldown < 0) { Buttoncooldown = 0; }
}



