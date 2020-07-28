// a shell built to handle all turret related transactions, including telling the turret what type it is and giving it its stats, store the prebuilt turrets, and alert the player when they reach the limit


#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "scene.h"
#include "game.h"
#include "cmp_turret.h"
#include "levelsystem.h"
#include "GUI.h"
//fixes one issue but makes another?
#ifndef Turretcontrol
#define Turretcontrol

using namespace std;
using namespace sf;

class TurretController {

protected:
	float cooldown = 0.05f;
	
	int turretpointer = 0;

public:
	TurretController();

	//i wish i knew a better way to do this right now
	std::vector<std::shared_ptr<Entity>> Turretlist;
	std::vector<std::shared_ptr<TurretComponent>> Componentlist;
	std::vector<Vector2f> Occupied;
	shared_ptr<GUI> gui;

	void Placeturret(string type);

	void update(double dt);
};



#endif // !Turretcontrol




