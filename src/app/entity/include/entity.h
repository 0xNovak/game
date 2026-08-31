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

struct IMoving {
  virtual void updatePosition(float deltaTime) = 0;
  auto getSpeed() -> float { return speed_m; }
  sf::Vector2f direction{0, 0};
  float speed_m{50};
};

static uint_fast64_t entityCount_s{0};
class Entity {
public:
  Entity(Hitbox hitbox, uint16_t spriteId)
      : hitbox_m(hitbox), spriteId(spriteId), Id(entityCount_s) {
    Log::debug(std::format("init entity (ID:{})", entityCount_s));
    entityCount_s++;
  };

  sf::Vector2f getPosition() { return position_m; }
  Hitbox getHitbox() { return hitbox_m; }
  sf::Vector2<uint8_t> getFrame() { return currentFrame_m; }

  const uint16_t spriteId{0};
  const uint16_t Id;

protected:
  Hitbox hitbox_m{};
  sf::Vector2f &position_m{hitbox_m.position}; // alias for easier acces;

private:
  sf::Vector2<uint8_t> currentFrame_m{0, 0};
};
} // namespace entity
