#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
namespace sgr::constants {
constexpr uint32_t FRAMERATE = 180;  // per sec
constexpr uint32_t UPDATERATE = 240; // per sec
constexpr sf::Vector2u WINDOW_SIZE{1280, 720};
}; // namespace sgr::constants
