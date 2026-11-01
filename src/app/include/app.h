#pragma once

#include "SFML/System/Vector2.hpp"
#include <engine.h>

#include <entity.h>
#include <playerCollection.h>
#include <utility>
#include <vector>
#include <worldManager.hpp>
class Application : public sgr::Engine {
  void init() override;
  void initResources();
  void initCurrentFloor();
  void update(float deltaTime) override;
  void initUSnap();
  void handleEvents(sf::RenderWindow &window) override;

  std::vector<entity::Entity *> eVector{};
  entity::Player *player{nullptr};
  world::RoomManager RoomCacheManager{};
  std::pair<sf::Vector2i, u8> gamePosition{{0, 0}, 0};

public:
  ~Application() {}
  // u32 seed;
};
