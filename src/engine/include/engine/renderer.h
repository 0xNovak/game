#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <unordered_map>

#include "SFML/Graphics/Texture.hpp"
#include "engine/render_entries.h"
namespace sgr::render {
class Renderer {
public:
  Renderer(sf::RenderWindow *window) : window_p(window) {};
  void render(const Snapshot *snap);

private:
  sf::RenderWindow *window_p;
};
struct AssetManager {
  const sf::Texture &get(uint16_t key);
  void init(uint16_t key, const char *assetPath);
  void initManager(uint32_t size);

private:
  std::unordered_map<uint16_t, const sf::Texture> hashMap{};
};
} // namespace sgr::render
