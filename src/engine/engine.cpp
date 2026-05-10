#include "engine.h"

#include <cstdint>
#include <mutex>
#include <stdexcept>
#include <thread>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowEnums.hpp"
#include "engine/render_entries.h"
#include "engine/renderer.h"

using namespace sgr;
void Engine::run() {
  engineInit();
  init();
  std::thread updateThread(&Engine::loopUpdate, this);
  loopRender();

  m_IsRunning.store(false);
  m_window.close();
  updateThread.join();
}

void Engine::engineInit() {
  m_window.create(sf::VideoMode{{1280u, 720u}}, "app", sf::Style::Close,
                  sf::State::Windowed);
  m_window.setFramerateLimit(FRAMERATE);
  m_window.setPosition({0, 0});
  assetManager.initManager(10);
}

void Engine::loopUpdate() {
  std::unordered_map<uint16_t, const sf::Texture> hashMap{};
  // hashMap.insert({0, sf::Texture{"resources/gfx/tmp.png"}});
  hashMap.emplace(0, sf::Texture{"resources/gfx/tmp.png"});
  const sf::Texture txt_TMP{"resources/gfx/tmp.png"};
  auto PositionY = 100.f;
  assetManager.init(0, "gfx/tmp.png");

  sf::Clock clock;
  const auto delay = 1'000'000 / UPDATERATE;
  int64_t nextUpdate = delay;
  int64_t lastUpdate = 0;

  while (m_IsRunning) {
    sf::sleep(
        sf::microseconds(nextUpdate - clock.getElapsedTime().asMicroseconds()));
    auto now = clock.getElapsedTime().asMicroseconds();
    nextUpdate = now + delay;
    auto deltaTime = now - lastUpdate;
    lastUpdate = now;

    updateSnap->vec.clear();
    update(deltaTime);

#define test_sprite
#ifdef test_sprite

    PositionY += .5f;
    if (PositionY > 200.f)
      PositionY = 100.f;

    auto txt_it = hashMap.find(0);
    if (txt_it == hashMap.end()) {
      m_IsRunning.store(false);
      throw std::runtime_error("txt 0 not found");
    }

    updateSnap->addEntry({0, sf::Sprite{txt_it->second}});
    updateSnap->addEntry({1, sf::Sprite{assetManager.get(0)}});
    updateSnap->addEntry({2, sf::Sprite{txt_TMP}});
    updateSnap->vec[0].sprite.setPosition({20, 100});
    updateSnap->vec[1].sprite.setPosition({50, 100});
    updateSnap->vec[2].sprite.setPosition({130, PositionY});
#endif // test_sprite
    {
      std::lock_guard<std::mutex> lock{snapMutex};
      std::swap(updateSnap, renderSnap);
    }
  }
}
void Engine::loopRender() {

  render::Renderer rendererUint{&m_window};
  while (m_IsRunning && m_window.isOpen()) {
    handleEvents(m_window);
    m_window.clear(sf::Color{30, 30, 30, 255});
    {
      std::lock_guard<std::mutex> lock{snapMutex};
      rendererUint.render(renderSnap);
    }
    m_window.display();
  }
  m_IsRunning.store(false);
  m_window.close();
}
