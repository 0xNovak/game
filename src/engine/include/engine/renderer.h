#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>

#include "engine/render_entries.h"
namespace sgr::render {

class Renderer {
public:
  Renderer(sf::RenderWindow *window) : window_p(window) {};
  void render(const Snapshot *snap);

private:
  sf::RenderWindow *window_p;
};
} // namespace sgr::render
