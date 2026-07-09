#include "app.h"

#include <array>
#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "engine/render_entries.h"
#include "engine/renderer.h"
#include "entity.h"
#include "entity/player.h"

using a = Application;

void a::init() {
  initResources();
  player = new entity::Player({0, 0}, 0);
  eVector.push_back(player);
}
void a::initResources() { assetManager.init(0, "gfx/tmp.png"); };
bool A_pressed{false};
void a::handleEvents(sf::RenderWindow &window) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      close();
  }
}

void a::update(float dt) {

  // --- Continuous key state for smooth movement ---

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    player->direction.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    player->direction.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    player->direction.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    player->direction.x += 1.f;

  player->updatePosition(dt);

  initUSnap();
}

void a::initUSnap() {
  for (auto e : eVector) {
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
            (int)chosen[Frame], (int)chosen[Row],
            (int)chosen[Row] > entry.frameAmount.size()
                ? std::format("row extends textures capability({})",
                              (int)entry.frameAmount.size())
                : std::format("frame extends rows frame capability({})",
                              (int)entry.frameAmount[chosen[Row]])));

      auto spSize = entry.frameSize;
      sf::Vector2i spPosi = {chosen[Frame] * spSize.x, chosen[Row] * spSize.y};
      sprt.setTextureRect({{spPosi}, {spSize}});
      return sprt;
    };
    updateSnap->addEntry({e->Id, getSprite(assetManager.get(e->spriteId))});
  }
}
