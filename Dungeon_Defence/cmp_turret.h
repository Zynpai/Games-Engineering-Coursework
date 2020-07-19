// a container for all turret related stats, including price, range, fire rate, damage, and the code to operate said turrets


#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "cmp_actor_movement.h"

class TurretComponent : public Component {
protected:
	//higher is better
	float _range;
	float _damage;

	//lower is better
	float _firerate;
	float _price;
	float _cooldown;

	float _bulletcounter = 0;

public:
	TurretComponent(Entity* p);

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
	
};






