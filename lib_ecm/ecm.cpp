#include "ecm.h"

using namespace std;
using namespace sf;


const sf::Vector2f & Entity::getPosition() const
{
	return _position;
}

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

bool Entity::is_fordeletion() const
{
	return _fordeletion;
}

float Entity::getRotation() const
{
	return _rotation;
}

void Entity::setRotation(float rotation)
{
	_rotation = rotation;
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::setAlive(bool alive)
{
	_alive = alive;
}

void Entity::setForDelete()
{
	_fordeletion = true;
}

bool Entity::isVisible() const
{
	return _visible;
}

void Entity::setVisible(bool visible)
{
	_visible = visible;
}

Entity::Entity()
{
}
Entity::~Entity()
{
}

void Entity::update(const double dt) {
	for each (auto c in _components) {
		c->update(dt);
	}
}

void Entity::render()
{
	for each (auto c in _components) {
		c->render();
	}
}


void EntityManager::update(double dt)
{
	for each (auto e in list)
	{
		if (e->isAlive()) { 
			e->update(dt); 
		}
		if (e->is_fordeletion()) {
			//delete the thing
		}
	}
}

void EntityManager::render()
{
	for each (auto e in list)
	{
		if (e->isVisible()) { 
			e->render(); 
		}
		
	}
}

Component::Component(Entity * const p) : _parent(p) {}

bool Component::is_fordeletion() const
{
	return _fordeletion;
}

Component::~Component()
{
}
