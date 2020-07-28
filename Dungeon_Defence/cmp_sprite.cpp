#include "cmp_sprite.h"
#include "system_renderer.h"

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

SpriteComponent::SpriteComponent(Entity* p) : Component(p) {
}

void SpriteComponent::update(double dt) {
	sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::render() { Renderer::queue(sprite.get()); }