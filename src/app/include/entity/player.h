#pragma once

#include "SFML/System/Vector2.hpp"
#include "entity.h"
#include <cstdint>
namespace entity {
class Player : public Entity {
public:
  Player(sf::Vector2f position, uint16_t spriteId)
      : Entity(position, spriteId) {};
  void updatePosition(float deltaTime);
  void move(sf::Vector2f deltaPosition);
  sf::Vector2f direction{0, 0};
};

} // namespace entity
