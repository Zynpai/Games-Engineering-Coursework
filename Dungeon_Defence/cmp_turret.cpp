// a container for all turret related stats, including price, range, fire rate, damage, and the code to operate said turrets

#include "cmp_turret.h"
#include <SFML/Graphics.hpp>
#include "ecm.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "scene.h"
#include "game.h"
#include "cmp_actor_movement.h"

using namespace std;
using namespace sf;

TurretComponent::TurretComponent(Entity* p)
	: Component(p) {
}

void TurretComponent::update(double dt) {
	//increment cooldown, then check if ready to fire
	if (_cooldown > 0) { _cooldown = _cooldown - dt; }
	if (_cooldown <= 0) {
		//rest of logic, including range check and firing bullet
	
	}



}

float TurretComponent::getRange() const { return _range; }
void TurretComponent::setRange(float range) { _range = range; }

float TurretComponent::getDamage() const { return _damage; }
void TurretComponent::setDamage(float damage) { _damage = damage; }

float TurretComponent::getRate() const { return _firerate; }
void TurretComponent::setRate(float rate) { 
	_firerate = rate;
	_cooldown = rate;
}

float TurretComponent::getPrice() const { return _price; }
void TurretComponent::setPrice(float price) { _price = price; }





