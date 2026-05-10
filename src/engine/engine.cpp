#include "engine.h"

#include <cstdint>
#include <mutex>
#include <thread>

#include "SFML/Graphics/RenderWindow.hpp"
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
  const auto delay = 1'000'000 / UPDATERATE;

  sf::Clock clock;
  int64_t lastUpdate = 0;
  auto now = [&clock]() { return clock.getElapsedTime().asMicroseconds(); };
  while (m_IsRunning) {
    sf::sleep(sf::microseconds(lastUpdate + delay - now()));

    updateSnap->vec.clear();
    update(now() - lastUpdate);
    lastUpdate = now();

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
