// a container for all turret related stats, including price, range, fire rate, damage, and the code to operate said turrets

#include "cmp_turret.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
void TurretComponent::setBulletTex(Texture tex) {

	for (int i = 0; i < Bulletlist.size(); i++) {
		auto s = Bulletlist.at(i)->addComponent<SpriteComponent>();
		s->sprite.setOrigin(4,8);
		s->setTexture(tex);
	}

}
void TurretComponent::update(double dt) {
	//increment cooldown, then check if ready to fire
	if (_cooldown > 0) { _cooldown = _cooldown - dt; }
	if (_cooldown <= 0) {
		if (!firing) {
			firing = true;
			//rest of logic, including range check and firing bullet
			//if the turret can shoot both air and ground, just search list
			if(targetAir && targetGround){
				for (int i = 0; i < Targetlist.size(); i++) {
					//dont shoot at dead enemeies
					if (Targetlist.at(i)->isAlive()) {
						float magnitude = sqrt(pow(Targetlist.at(i)->getPosition().x - _parent->getPosition().x, 2) + pow(Targetlist.at(i)->getPosition().y - _parent->getPosition().y, 2));
						//if in range, shoot
						if (magnitude <= _range) {
							Componentlist.at(_bulletcounter)->target = Targetlist.at(i);
							Componentlist.at(_bulletcounter)->targetComponent = creepComponentlist.at(i);
							Componentlist.at(_bulletcounter)->targeted = true;
							Bulletlist.at(_bulletcounter)->setPosition(_parent->getPosition());
							Bulletlist.at(_bulletcounter)->setAlive(true);
							Bulletlist.at(_bulletcounter)->setVisible(true);
							_bulletcounter++;
							if (_bulletcounter > 2) {
								_bulletcounter = 0;
							}
							_cooldown = _firerate;
							break;
						}
						
					
					}
				}
			}
			//else, check what the turret can shoot against list of enemies, and check state of enemies for match
			else if(targetAir){
				for (int i = 0; i < Targetlist.size(); i++) {
					if (Targetlist.at(i)->isAlive() && creepComponentlist.at(i)->flying) {
						float magnitude = sqrt(pow(Targetlist.at(i)->getPosition().x - _parent->getPosition().x, 2) + pow(Targetlist.at(i)->getPosition().y - _parent->getPosition().y, 2));
						//if in range, shoot
						if (magnitude <= _range) {
							Componentlist.at(_bulletcounter)->target = Targetlist.at(i);
							Componentlist.at(_bulletcounter)->targetComponent = creepComponentlist.at(i);
							Componentlist.at(_bulletcounter)->targeted = true;
							Bulletlist.at(_bulletcounter)->setPosition(_parent->getPosition());
							Bulletlist.at(_bulletcounter)->setAlive(true);
							Bulletlist.at(_bulletcounter)->setVisible(true);
							_bulletcounter++;
							if (_bulletcounter > 2) {
								_bulletcounter = 0;
							}
							_cooldown = _firerate;
							break;
						}


					}
				}
			}
			else if (targetGround) {
				for (int i = 0; i < Targetlist.size(); i++) {
					if (Targetlist.at(i)->isAlive() && !creepComponentlist.at(i)->flying) {
						float magnitude = sqrt(pow(Targetlist.at(i)->getPosition().x - _parent->getPosition().x, 2) + pow(Targetlist.at(i)->getPosition().y - _parent->getPosition().y, 2));
						//if in range, shoot
						if (magnitude <= _range) {
							Componentlist.at(_bulletcounter)->target = Targetlist.at(i);
							Componentlist.at(_bulletcounter)->targetComponent = creepComponentlist.at(i);
							Componentlist.at(_bulletcounter)->targeted = true;
							Bulletlist.at(_bulletcounter)->setPosition(_parent->getPosition());
							Bulletlist.at(_bulletcounter)->setAlive(true);
							Bulletlist.at(_bulletcounter)->setVisible(true);
							_bulletcounter++;
							if (_bulletcounter > 2) {
								_bulletcounter = 0;
							}
							_cooldown = _firerate;
							break;
						}


					}

				}
			}
			

			firing = false;
		}
		
		
	}



}

float TurretComponent::getRange() const { return _range; }
void TurretComponent::setRange(float range) { _range = range; }

void TurretComponent::setDamage(float damage) {
	for (int i = 0; i < Bulletlist.size(); i++) {
		Componentlist.at(i)->damage = damage;
	}
}

float TurretComponent::getRate() const { return _firerate; }
void TurretComponent::setRate(float rate) { 
	_firerate = rate;
	_cooldown = rate;
}
