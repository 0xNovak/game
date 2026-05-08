#include "engine.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowEnums.hpp"
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
}
void Engine::loopUpdate() {
  // -- test --
  // const sf::Texture txt_TMP{"resources/gfx/tmp.png"};
  // {
  //   render::RenderEntry entry{0, sf::Sprite{txt_TMP}};
  //   updateSnap->addEntry(entry);
  // }
  // updateSnap->vec[0].sprite.setPosition({200.f, 200.f});
  while (m_IsRunning) {

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
