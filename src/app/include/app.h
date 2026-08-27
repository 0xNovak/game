#pragma once

#include "playerCollection.h"
#include <engine.h>

#include <entity.h>
#include <vector>

class Application : public sgr::Engine {
  void init() override;
  void initResources();
  void update(float deltaTime) override;
  void initUSnap();
  void handleEvents(sf::RenderWindow &window) override;

  std::vector<entity::Entity *> eVector{};
  entity::Player *player{nullptr};

public:
  ~Application() {}
};
