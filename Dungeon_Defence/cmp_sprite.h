#pragma once
#include "ecm.h"

using namespace std;
using namespace sf;

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;
public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	sf::Shape &getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

//tried to get this to work, did not work in end
class SpriteComponent : public Component {
public:
	Texture tex;
	SpriteComponent(Entity *p);
	Sprite sprite;
	void update(double dt) override;
	void render() override;
	void setTexture(Texture tex);

};