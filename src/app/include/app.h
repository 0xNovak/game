#pragma once
#include <engine.h>
class Application : public sgr::Engine {
  void init() override;
  void update(uint64_t deltaTime) override;
  void handleEvents(sf::RenderWindow &window) override;

public:
  ~Application() {}
};
