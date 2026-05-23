#include "app.h"
#include <cstdint>

using a = Application;
void a::init() {}
void a::update(uint64_t deltaTime) {}
void a::handleEvents(sf::RenderWindow &window) {
  while (const std::optional event = window.pollEvent())
    if (event->is<sf::Event::Closed>())
      close();
};
