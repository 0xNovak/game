#include "engine.h"

#include <format>
#include <mutex>
#include <thread>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowEnums.hpp"

#include "engine/render_entries.h"
#include "engine/renderer.h"

#include "./logEngine.h"

using namespace sgr;
void Engine::run() {
  LogEng::info("engine init");
  engineInit();
  init();

  LogEng::info("engine \033[32mSUCCESFUL\033[0m");
  std::thread updateThread(&Engine::loopUpdate, this);
  loopRender();

  m_IsRunning.store(false);
  m_window.close();
  updateThread.join();
}

void Engine::engineInit() {
  LogEng::info("  window");
  m_window.create(sf::VideoMode{WINDOW_SIZE}, "app", sf::Style::Close,
                  sf::State::Windowed);
  m_window.setFramerateLimit(FRAMERATE);
  m_window.setPosition({0, 0});
  assetManager.initManager(10);
  LogEng::info("  window \033[32mOK\033[0m");
}

void Engine::loopUpdate() {
  constexpr auto DELAY = 1.f / UPDATERATE;

  sf::Clock clock;
  float lastUpdate = 0;
  auto now = [&clock]() { return clock.getElapsedTime().asSeconds(); };
  while (m_IsRunning) {
    sf::sleep(sf::seconds(lastUpdate + DELAY - now()));

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
    m_window.clear(sf::Color{30, 30, 30, 255});
    {
      std::lock_guard<std::mutex> lock{snapMutex};
      handleEvents(m_window);
      rendererUint.render(renderSnap);
    }
    m_window.display();
  }
  m_IsRunning.store(false);
  m_window.close();
}
