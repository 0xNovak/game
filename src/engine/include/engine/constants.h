#pragma once

#include "SFML/System/Vector2.hpp"
#include <ussableInt.h>
namespace sgr::constants {
constexpr u32 FRAMERATE = 180;                  // per sec
constexpr u32 UPDATERATE = 240;                 // per sec
constexpr sf::Vector2u WINDOW_SIZE{1440, 1080}; // 60x45 grid of (24x24) tiles
}; // namespace sgr::constants
