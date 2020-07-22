// a shell built to handle all turret related transactions, including telling the turret what type it is and giving it its stats, store the prebuilt turrets, and alert the player when they reach the limit


#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "scene.h"
#include "game.h"
#include "cmp_turret.h"

class TurretController {

protected:


public:


	//i wish i knew a better way to do this right now
	std::vector<std::shared_ptr<Entity>> Turretlist;
	std::vector<std::shared_ptr<TurretComponent>> Componentlist;

	void Placeturret();


};




