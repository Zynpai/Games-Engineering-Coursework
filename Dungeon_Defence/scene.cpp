#include "scene.h"

void Scene::update(double dt) { _em.update(dt); }
void Scene::render() { _em.render(); }
void Scene::load() {}
std::vector<std::shared_ptr<Entity>> &Scene::getEnts() { return _em.list; }