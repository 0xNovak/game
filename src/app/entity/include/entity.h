#pragma once

#include <array>
#include <cstdint>

#include "SFML/System/Vector2.hpp"
#include <SFML/System.hpp>

#include "log.h"

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
    Log::debug(std::format("init entity (ID:{})", entityCount_s));
    entityCount_s++;
  };
  virtual void updatePosition(float deltaTime);

  auto getPosition() -> sf::Vector2f { return position_m; }
  auto getHitbox() -> Hitbox { return hitbox_m; }
  auto getFrame() -> std::array<uint8_t, 2> { return currentFrame_m; }
  auto getSpeed() -> float { return speed_m; }

  sf::Vector2f direction{0, 0};

  const uint16_t spriteId{0};
  const uint16_t Id;

protected:
  float speed_m{50};

  Hitbox hitbox_m{};
  sf::Vector2f &position_m{hitbox_m.position}; // alias for easier acces;

private:
  std::array<uint8_t, 2> currentFrame_m{0, 0};
};
} // namespace entity
