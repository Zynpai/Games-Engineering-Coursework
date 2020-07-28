// handle wave related stuff


#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "Wave_controller.h"

using namespace std;
using namespace sf;

WaveController::WaveController() {
	//on creation load all textures into vector
	//sf::Texture tex;
	//if (!tex.loadFromFile("res/sprites/EagleIdle.png")) {
		//error
	//	throw string("failed to load texture");
	//}
	//texturelist.push_back(tex);
	//if (!tex.loadFromFile("res/sprites/FootManIdle.png")) {
		//error
	//	throw string("failed to load texture");
	//}
	//texturelist.push_back(tex);
	//if (!tex.loadFromFile("res/sprites/RogueIdle.png")) {
		//error
	//	throw string("failed to load texture");
	//}
	//texturelist.push_back(tex);
}



void WaveController::update(double dt) {
	if (cooldown > 0) { 
		cooldown = cooldown - dt; 
		//doing this to help display time better
		if (cooldown < 0) { cooldown = 0; }
		gui->updateTimer(floor(cooldown));
	}
	if (cooldown == 0) {
		//spawn the next wave
		if (spacing > 0) { spacing = spacing - dt; }
		if (spacing <= 0) {

			Creeplist.at(creepPointer)->setPosition(ls::findTiles(ls::END)[1]);
			//basic health scale, can be changed later
			Componentlist.at(creepPointer)->health = 10 * waveNo;
			Componentlist.at(creepPointer)->reward = 1 * waveNo;
			//every 5th wave is flying, can be adjusted or changed
			if (waveNo % 5 == 0) {
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(0));
				Componentlist.at(creepPointer)->flying = true;
			}
			else if (waveNo % 2 == 0) {
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(2));
			}
			else {
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(1));
			}

			Creeplist.at(creepPointer)->setAlive(true);
			Creeplist.at(creepPointer)->setVisible(true);
			creepPointer = creepPointer + 1;
			spacing = 0.6f;
		}


		//time between waves, can be adjusted
		if (creepPointer == 20) {

			cooldown = 30.0f;
			waveNo = waveNo + 1;
			creepPointer = 0;
		}
	}

}