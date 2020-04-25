#pragma once

#include <SFML/Graphics.hpp>
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component;

class Entity {

protected:
	
	sf::Vector2f _position;
	float _rotation;
	bool _alive = true;       // should be updated
	bool _visible = true;     // should be rendered
	bool _fordeletion = false; // should be deleted
public:
	std::vector<std::shared_ptr<Component>> _components;
	Entity();
	virtual ~Entity();
	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f &getPosition() const;
	void setPosition(const sf::Vector2f &_position);
	bool is_fordeletion() const;
	float getRotation() const;
	void setRotation(float _rotation);
	bool isAlive() const;
	void setAlive(bool _alive);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _visible);


	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};


class Component {
protected:
	Entity *const _parent;
	bool _fordeletion; // should be removed
	explicit Component(Entity *const p);

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};