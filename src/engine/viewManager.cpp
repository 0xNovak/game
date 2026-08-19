#include "engine/viewManager.h"

#include <cstdint>
#include <format>
#include <stdexcept>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/View.hpp"

#include "SFML/System/Vector2.hpp"
#include "engine/constants.h"

using VMan = sgr::render::view::ViewManager;

const sf::View &VMan::get(uint8_t key) const {
  auto it = hashMap.find(key);
  if (it != hashMap.end())
    return it->second;
  throw std::runtime_error(
      std::format("view under key {} havent been loaded properly", key));
}
sf::View &VMan::edit(uint8_t key) {
  auto it = hashMap.find(key);
  if (it != hashMap.end())
    return it->second;
  throw std::runtime_error(
      std::format("view under key {} havent been loaded properly", key));
}

void VMan::init(uint8_t key, sf::View view) { hashMap.emplace(key, view); }
void VMan::initManager(uint8_t size) {
  using namespace sgr::constants;
  hashMap.reserve(size);
  sf::View stdMainView{{0, 0}, static_cast<sf::Vector2f>(WINDOW_SIZE)};
  hashMap.emplace(0, stdMainView);
}
