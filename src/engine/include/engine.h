#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>

#include "SFML/Graphics/RenderWindow.hpp"
#include "engine/render_entries.h"
#include "engine/renderer.h"

namespace sgr {
class Engine {
public:
  Engine() {};
  virtual ~Engine() {};
  void run();

protected:
  virtual void init() = 0;
  virtual void update(uint64_t deltaTime) = 0;
  virtual void handleEvents(sf::RenderWindow &window) = 0;

  void close() { m_IsRunning.store(false); };

  render::Snapshot *renderSnap{&snapA}, *updateSnap{&snapB};

private:
  void loopUpdate();
  void loopRender();
  void engineInit();

  sf::RenderWindow m_window;
  std::atomic<bool> m_IsRunning{true};

  render::Snapshot snapA, snapB;
  std::mutex snapMutex;
  render::AssetManager assetManager;
};
constexpr uint32_t FRAMERATE = 120;  // per sec
constexpr uint32_t UPDATERATE = 144; // per sec
constexpr sf::Vector2u WINDOW_SIZE{1280, 720};
} // namespace sgr
