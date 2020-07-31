#include "cmp_sprite.h"
#include "system_renderer.h"
using namespace std;
using namespace sf;

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

SpriteComponent::SpriteComponent(Entity* p) : Component(p) {
}

void SpriteComponent::update(double dt) {
	sprite.setPosition(_parent->getPosition());
}

void SpriteComponent::setTexture(Texture texture) {
	tex = texture;
}
void SpriteComponent::render() { 
	sprite.setTexture(tex);
	Renderer::getWindow().draw(sprite);
}