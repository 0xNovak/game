#include "engine/renderer.h"

#include "SFML/Graphics/Texture.hpp"
#include "engine/render_entries.h"
#include <algorithm>
#include <cstdint>
#include <format>
#include <stdexcept>
#include <vector>

using namespace sgr::render;
void Renderer::render(const Snapshot *snap) {
  std::vector<RenderEntry> sorted;
  sorted.reserve(snap->vec.size());
  for (auto entry : snap->vec)
    sorted.push_back(entry);

  std::sort(sorted.begin(), sorted.end(),
            [](const RenderEntry &a, const RenderEntry &b) {
              auto A_pos = a.sprite.getPosition(),
                   B_pos = b.sprite.getPosition();
              if (A_pos.y != B_pos.y)
                return A_pos.y > B_pos.y;
              return a.id < b.id;
            });
  for (auto entry : sorted) {
    window_p->setView(viewManager.get(entry.viewID));
    window_p->draw(entry.sprite);
  }
}

const AssetEntry &AssetManager::get(uint16_t key) const {
  auto it = hashMap.find(key);
  if (it != hashMap.end())
    return it->second;
  throw std::runtime_error(
      std::format("texture under key {} havent been loaded properly", key));
}

void AssetManager::init(uint16_t key, const char *assetPath) {
  AssetEntry asset{
      .texture =
          sf::Texture{sf::Texture{std::format("resources/{}", assetPath)}},
      .frameSize = {2,
                    2}, //{24, 32}, // TODO: read data of texture to get these
      .frameAmount = {1}};
  hashMap.emplace(key, asset);
}
void AssetManager::initManager(uint16_t size) { hashMap.reserve(size); }
