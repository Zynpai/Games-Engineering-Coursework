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
			//every 5th wave is flying, can be adjusted or changed
			if (int(waveNo) % 5 == 0) {
				//eagle, fast, frail and flying
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(0));
				Componentlist.at(creepPointer)->flying = true;
				Componentlist.at(creepPointer)->health = 5 * waveNo;
				//placeholder, unknown how fast this is
				Componentlist.at(creepPointer)->setSpeed(350.0f);
			}
			else if (int(waveNo) % 2 == 0) {
				//rogue, fast but frail
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(2));
				Componentlist.at(creepPointer)->flying = false;
				Componentlist.at(creepPointer)->health = 5 * waveNo;
				//placeholder, unknown how fast this is
				Componentlist.at(creepPointer)->setSpeed(300.0f);
			}
			else {
				//footman, slow but tough
				//spriteList.at(creepPointer)->sprite->setTexture(texturelist.at(1));
				Componentlist.at(creepPointer)->flying = false;
				Componentlist.at(creepPointer)->health = 10 * waveNo;
				//1 armor every 4 waves
				Componentlist.at(creepPointer)->armor = floor(0.25*waveNo);
				//placeholder, unknown how fast this is
				Componentlist.at(creepPointer)->setSpeed(200.0f);
			}
			//wave 1 & 2 = 1, 3 & 4 = 2 etc....
			Componentlist.at(creepPointer)->reward = floor(0.51 + waveNo / 2);

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