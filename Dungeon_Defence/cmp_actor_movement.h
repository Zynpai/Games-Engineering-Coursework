#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>





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

	void render() override {}
	void update(double dt) override;
};

class BulletMovementComponent : public ActorMovementComponent {
public:
	BulletMovementComponent(Entity* p);
	Entity target;
	//true if going towards an entity, false if going in a line, default false
	bool targeted = false;
	sf::Vector2f VecTarget;
	float damage;
	void update(double dt) override;
};




//for enemy use
class CreepMovementComponent : public ActorMovementComponent {
public:
	CreepMovementComponent(Entity* p);
	void update(double dt) override;
};