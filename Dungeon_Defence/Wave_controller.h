//handle wave related stuff

#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "scene.h"
#include "game.h"
#include "cmp_actor_movement.h"
#include "levelsystem.h"


using namespace std;
using namespace sf;

class WaveController {

protected:
	//30 seconds to learn controls, and place towers before 1st wave
	float cooldown = 30.0f;
	//time between each creep spawn, can be adjusted to make waves denser or sparser
	float spacing = 0.6f;

	int creepPointer = 0;

	
public:
	//what wave we are on, can be used for scaling and special waves, must be float for dividing
	float waveNo = 1;
	WaveController();
	shared_ptr<GUI> gui;
	//i wish i knew a better way to do this right now
	std::vector<std::shared_ptr<Entity>> Creeplist;
	std::vector<std::shared_ptr<ShapeComponent>> Shapelist;
	std::vector<std::shared_ptr<CreepMovementComponent>> Componentlist;
	//std::vector<std::shared_ptr<SpriteComponent>> spriteList;
	//std::vector<sf::Texture> texturelist;

	void update(double dt);
	void skip();
};



