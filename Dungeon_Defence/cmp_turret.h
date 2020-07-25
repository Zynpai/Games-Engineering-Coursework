// a container for all turret related stats, including price, range, fire rate, damage, and the code to operate said turrets
#pragma once
#include "cmp_actor_movement.h"
#include <SFML/Graphics.hpp>
#include <ecm.h>


using namespace sf;
using namespace std;


class TurretComponent : public Component {
protected:
	//higher is better
	float _range =0;
	float _damage =0;

	//lower is better
	float _firerate =1;
	float _price =0;
	float _cooldown =1;

	float _bulletcounter = 0;
	bool firing = false;

public:
	TurretComponent(Entity* p);

	std::vector<std::shared_ptr<Entity>> Targetlist;

	std::vector<std::shared_ptr<Entity>> Bulletlist;
	std::vector<std::shared_ptr<BulletMovementComponent>> Componentlist;

	float getRange() const;
	void setRange(float _range);

	float getDamage() const;
	void setDamage(float _damage);

	float getRate() const;
	void setRate(float _firerate);

	float getPrice() const;
	void setPrice(float _price);

	void update(double dt) override;
	void render() override {}


	bool targetAir = false;
	bool targetGround = false;
};






