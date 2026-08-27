#pragma once

#include "SFML/System/Vector2.hpp"
#include "entity.h"

#include <cstdint>
#include <limits>

namespace entity {
class Player : public Entity {
public:
  Player(Hitbox hitbox, uint16_t spriteId) : Entity(hitbox, spriteId) {};
  void handleInput();
  void updatePosition(float deltaTime) override;
  float invincibilityTLeft{0};

private:
  struct Roll {
    float cooldown{0.75f};
    float sinceLast{std::numeric_limits<float>::infinity()};
    sf::Vector2f direction{0.f, 0.f};
    float left{0};
    float duration{0.25f};
    float speedMultiplier{25};
  };
  Roll roll_m;
};

} // namespace entity
