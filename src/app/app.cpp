#include "app.h"

#include <array>
#include <utility>
#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"

#include "engine/render_entries.h"
#include "engine/renderer.h"
#include "entity.h"
#include "entity/player.h"
#include "sfVectorOps.h"

#include <log.h>

using a = Application;

void a::init() {
  initResources();
  entity::Hitbox T_hbx{{0.f, 0.f}, {24, 32}};
  player = new entity::Player(std::move(T_hbx), 0);
  eVector.push_back(player);
}
void a::initResources() { assetManager.init(0, "gfx/debug.png"); }
bool A_pressed{false};
void a::handleEvents(sf::RenderWindow &window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      close();
    if (event->is<sf::Event::FocusLost>())
      continue;
    // TODO: add stop implementation
  }
}

void a::update(float dt) {
  player->handleInput();
  for (auto E : eVector)
    E->updatePosition(dt);
  initUSnap();
}

void a::initUSnap() {
  for (const auto e : eVector) {
    auto getSprite = [&e](const sgr::render::AssetEntry &entry) -> sf::Sprite {
      sf::Sprite sprt{entry.texture};
      sprt.setPosition(e->getPosition());

      auto chosen = e->getFrame();
      enum FRAME_LOCATION { Frame = 0, Row = 1 };
      if (chosen[Row] > entry.frameAmount.size() ||
          chosen[Frame] >= entry.frameAmount[chosen[Row]])
        throw std::runtime_error(std::format(
            "frame given by Entity does fit in the texture "
            "bounds \n given : {}/{}  {} ",
            static_cast<int>(chosen[Frame]), static_cast<int>(chosen[Row]),
            static_cast<int>(chosen[Row]) > entry.frameAmount.size()
                ? std::format("row extends textures capability({})",
                              static_cast<int>(entry.frameAmount.size()))
                : std::format(
                      "frame extends rows frame capability({})",
                      static_cast<int>(entry.frameAmount[chosen[Row]]))));
      auto spSize = entry.frameSize;
      sf::Vector2i spPosi = {chosen[Frame] * spSize.x, chosen[Row] * spSize.y};
      sprt.setTextureRect({{spPosi}, {spSize}});
      auto e_size{e->getHitbox().size};
      auto scale{e_size / spSize};
      sprt.setScale(scale);
      return sprt;
    };
    updateSnap->addEntry({e->Id, getSprite(assetManager.get(e->spriteId))});
  }
}
