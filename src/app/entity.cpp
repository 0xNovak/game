#include "entity.h"
using namespace entity;
void Entity::move(sf::Vector2f deltaPosition) { position_m += deltaPosition; }
void Entity::updatePosition(float dt) {
  if (direction == sf::Vector2f{})
    return;
  speed_m = 125;
  sf::Vector2f positionDelta = direction * speed_m * dt;
  if (direction.length() != 0) {
    positionDelta = positionDelta.normalized();
  }
  position_m += positionDelta;
  direction = {0, 0};
}
