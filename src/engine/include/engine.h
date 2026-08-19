#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>

#include "SFML/Graphics/RenderWindow.hpp"
#include "engine/constants.h"
#include "engine/render_entries.h"
#include "engine/renderer.h"
#include "engine/viewManager.h"

namespace sgr {
class Engine {
public:
  Engine() {};
  virtual ~Engine() {};
  void run();

protected:
  virtual void init() = 0;
  virtual void update(float deltaTime) = 0;
  virtual void editView() {};
  virtual void handleEvents(sf::RenderWindow &window) = 0;
  void close() { m_IsRunning.store(false); };

  render::Snapshot *renderSnap{&snapA}, *updateSnap{&snapB};
  render::AssetManager assetManager;
  render::view::ViewManager viewManager;

private:
  void loopUpdate();
  void loopRender();
  void engineInit();

  sf::RenderWindow m_window;
  std::atomic<bool> m_IsRunning{true};

  std::mutex snapMutex;
  render::Snapshot snapA, snapB;
};
} // namespace sgr
