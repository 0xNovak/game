#pragma once

#include "entity.h"

#include <cstdint>

namespace entity {
class Player : public Entity {
public:
  Player(Hitbox hitbox, uint16_t spriteId) : Entity(hitbox, spriteId) {};
  void handleInput();
};

} // namespace entity
