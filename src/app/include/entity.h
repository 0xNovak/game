#pragma once

#include <array>
#include <cstdint>

#include "SFML/System/Vector2.hpp"
#include <SFML/System.hpp>

namespace entity {
struct Hitbox {
  sf::Vector2f position{};
  sf::Vector2i size{};
};
static uint_fast64_t entityCount_s{0};
class Entity {
public:
  Entity(Hitbox hitbox, uint16_t spriteId)
      : hitbox_m(hitbox), spriteId(spriteId), Id(entityCount_s) {
    entityCount_s++;
  };
  virtual void updatePosition(float deltaTime);

  // clang-format off
  sf::Vector2f getPosition() { return position_m; }
  auto getHitbox()           { return hitbox_m; }
  auto getFrame()            { return currentFrame_m; }
  float getSpeed()           { return speed_m; }
  // clang-format on

  sf::Vector2f direction{0, 0};

  const uint16_t spriteId{0};
  const uint16_t Id;

protected:
  float speed_m{10};

  Hitbox hitbox_m{};
  sf::Vector2f &position_m{hitbox_m.position}; // alias for easier acces;

private:
  std::array<uint8_t, 2> currentFrame_m{0, 0};
};
} // namespace entity
