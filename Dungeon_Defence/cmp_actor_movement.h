#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ecm.h>
#include "GUI.h"


using namespace std;

class ActorMovementComponent : public Component {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float _speed);

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void Uncheckedmove(const sf::Vector2f&);
	void Uncheckedmove(float x, float y);

	void render() override {}
	void update(double dt) override;
};

//for enemy use
class CreepMovementComponent : public ActorMovementComponent {
protected:
	enum STATE { ROAMING, ROTATING, ROTATED };
	STATE _state;
	sf::Vector2i oldDir = sf::Vector2i{ 0, 1 };

public:
	sf::Vector2f _direction;
	//wall for wall ability checks
	shared_ptr<Entity> wall;
	float health;
	//if true, airborne, if false, grounded
	bool flying;
	//money obtained on kill
	int reward;
	shared_ptr<GUI> gui;
	//some special properties?
	//float regenAmount : every second heal health by this? (would also require a maxhealth var)
	float armor = 0; //: reduce incomming damage by amount listed? (maybe have a min damage so that any tower can still hurt)
	//bool/float acceleration : slowly speed up while going through the map, by a set amount or custom amount?


	CreepMovementComponent(Entity* p);
	void update(double dt) override;
};

class BulletMovementComponent : public ActorMovementComponent {
public:
	BulletMovementComponent(Entity* p);
	//for use with targeted bullets
	shared_ptr<Entity> target;
	shared_ptr<CreepMovementComponent> targetComponent;
	shared_ptr<GUI> gui;
	//for use with untargeted bullets
	vector<shared_ptr<Entity>> Creeplist;
	vector<shared_ptr<CreepMovementComponent>> CreepComponentlist;
	//true if going towards an entity, false if going in a line, default false
	bool targeted = false;
	sf::Vector2f VecTarget;
	float damage;
	void update(double dt) override;
};




