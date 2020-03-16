//#include "Player.h"
//#include "system_renderer.h"
//#include "levelsystem.h"
//
//using namespace sf;
//using namespace std;
//
//void Player::update(double dt) {
//	
//	if (Keyboard::isKeyPressed(Keyboard::Left)) {
//		_valid = validMove(Vector2f(-_speed, 0.0f)*float(dt) + _position);
//		if (_valid) {
//			move(Vector2f(-_speed, 0.0f)*float(dt));
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Right)) {
//		_valid = validMove(Vector2f(_speed, 0.0f)*float(dt) + _position);
//		if (_valid) {
//			move(Vector2f(_speed, 0.0f)*float(dt));
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Up)) {
//		_valid = validMove(Vector2f(0.0f, -_speed)*float(dt) + _position);
//		if (_valid) {
//			move(Vector2f(0.0f, -_speed)*float(dt));
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Down)) {
//		_valid = validMove(Vector2f(0.0f, _speed)*float(dt) + _position);
//		if (_valid) {
//			move(Vector2f(0.0f, _speed)*float(dt));
//		}
//	}
//	
//	
//	Entity::update(dt);
//}
//
//Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)){
//
//	_shape->setFillColor(Color::Yellow);
//	_shape->setOrigin(Vector2f(25.0f, 25.0f));
//
//
//}
//
//void Player::render() const {
//
//	Renderer::queue(_shape.get());
//}
//
//void Player::Load(Vector2f pos) {
//
//	move(pos);
//	_won = false;
//
//}
//bool Player::validMove(Vector2f pos) {
//	return true;// (ls::getTileAt(pos) != ls::WALL);
//}