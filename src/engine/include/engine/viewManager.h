#pragma once

#include <cstdint>
#include <unordered_map>

#include "SFML/Graphics/View.hpp"

namespace sgr::render::view {
struct ViewManager {
  const sf::View &get(uint8_t key) const;
  sf::View &edit(uint8_t key);
  void init(uint8_t key, sf::View);
  void initManager(uint8_t size);

private:
  std::unordered_map<uint8_t, sf::View> hashMap{};
};

} // namespace sgr::render::view
