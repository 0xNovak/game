#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace sgr::render {

struct RenderEntry {
  uint32_t id;
  sf::Sprite sprite;
  uint8_t viewID{0};
};
struct Snapshot {
  Snapshot() { vec.reserve(30); }
  void addEntry(RenderEntry entry) { vec.push_back(entry); }

  std::vector<RenderEntry> vec;
};
} // namespace sgr::render
