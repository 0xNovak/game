#include "engine/viewManager.h"

#include <format>
#include <stdexcept>
#include <ussableInt.h>

#include "SFML/Graphics/View.hpp"

#include "SFML/System/Vector2.hpp"
#include "engine/constants.h"

using VMan = sgr::render::view::ViewManager;

const sf::View &VMan::get(u8 key) const {
  auto it = hashMap.find(key);
  if (it != hashMap.end())
    return it->second;
  throw std::runtime_error(
      std::format("view under key {} havent been loaded properly", key));
}
sf::View &VMan::edit(u8 key) {
  auto it = hashMap.find(key);
  if (it != hashMap.end()) [[likely]]
    return it->second;
  throw std::runtime_error(
      std::format("view under key {} havent been loaded properly", key));
}

void VMan::init(u8 key, sf::View view) { hashMap.emplace(key, view); }
void VMan::initManager(u8 size) {
  using namespace sgr::constants;
  hashMap.reserve(size);
  sf::View stdMainView{{0, 0}, static_cast<sf::Vector2f>(WINDOW_SIZE)};
  hashMap.emplace(0, stdMainView);
}
