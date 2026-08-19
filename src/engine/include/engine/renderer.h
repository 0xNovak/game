#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "SFML/Graphics/Texture.hpp"

#include "SFML/Graphics/View.hpp"
#include "engine/render_entries.h"
#include "engine/viewManager.h"

namespace sgr::render {
using namespace sgr::render::view;
class Renderer {
public:
  Renderer(sf::RenderWindow *window, ViewManager &viewManager)
      : window_p(window), viewManager(viewManager) {};
  void render(const Snapshot *snap);

private:
  sf::RenderWindow *window_p;
  ViewManager &viewManager;
};
struct AssetEntry {
  const sf::Texture texture;
  sf::Vector2i frameSize{24, 32};
  std::vector<uint8_t> frameAmount{1}; // per row frame amount
};
struct AssetManager {
  const AssetEntry &get(uint16_t key) const;
  void init(uint16_t key, const char *assetPath);
  void initManager(uint16_t size);

private:
  std::unordered_map<uint16_t, AssetEntry> hashMap{};
};
} // namespace sgr::render
