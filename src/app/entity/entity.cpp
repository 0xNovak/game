#include "entity.h"
using namespace entity;
void Entity::updatePosition(float dt) {
  if (direction == sf::Vector2f{0, 0})
    return;
  sf::Vector2f positionDelta = direction.normalized() * speed_m * dt;
  position_m += positionDelta;
  direction = {0, 0};
}
