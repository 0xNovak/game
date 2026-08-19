#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
namespace sgr::constants {
constexpr uint32_t FRAMERATE = 120;  // per sec
constexpr uint32_t UPDATERATE = 144; // per sec
constexpr sf::Vector2u WINDOW_SIZE{1280, 720};
}; // namespace sgr::constants
