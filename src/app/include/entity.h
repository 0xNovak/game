#pragma once

#include <array>
#include <cstdint>

#include "SFML/System/Vector2.hpp"
#include <SFML/System.hpp>

namespace entity {
static uint_fast64_t entityCount_s{0};
class Entity {
public:
  Entity(sf::Vector2f position, uint16_t spriteId)
      : position_m(position), spriteId(spriteId), Id(entityCount_s) {
    entityCount_s++;
  };
  sf::Vector2f getPosition() { return position_m; }
  std::array<uint8_t, 2> getFrame() { return currentFrame_m; }
  float getSpeed() { return speed_m; };
  const uint16_t spriteId{0};
  const uint16_t Id;

protected:
  float speed_m{10};
  sf::Vector2f position_m{0, 0};

private:
  std::array<uint8_t, 2> currentFrame_m{0, 0};
};

} // namespace entity
