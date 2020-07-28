//handle wave related stuff


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
	//60 seconds to learn controls, and place towers before 1st wave
	float cooldown = 1.0f;
	//time between each creep spawn, can be adjusted to make waves denser or sparser
	float spacing = 0.5f;

	int creepPointer = 0;

	//what wave we are on, can be used for scaling and special waves
	int waveNo = 1;
public:
	WaveController();
	shared_ptr<GUI> gui;
	//i wish i knew a better way to do this right now
	std::vector<std::shared_ptr<Entity>> Creeplist;
	std::vector<std::shared_ptr<CreepMovementComponent>> Componentlist;


	void update(double dt);
};



