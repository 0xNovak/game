#include "engine/renderer.h"

#include "SFML/Graphics/Texture.hpp"
#include "engine/render_entries.h"
#include <algorithm>
#include <cstdint>
#include <execution>
#include <format>
#include <stdexcept>
#include <vector>

using namespace sgr::render;
void Renderer::render(const Snapshot *snap) {
  std::vector<RenderEntry> sorted;
  sorted.reserve(snap->vec.size());
  for (auto entry : snap->vec)
    sorted.push_back(entry);

  std::sort(std::execution::seq, sorted.begin(), sorted.end(),
            [](const RenderEntry &a, const RenderEntry &b) {
              auto A_pos = a.sprite.getPosition(),
                   B_pos = b.sprite.getPosition();
              if (A_pos.y != B_pos.y)
                return A_pos.y > B_pos.y;
              return a.id < b.id;
            });
  for (auto entry : sorted)
    window_p->draw(entry.sprite);
}

const AssetEntry &AssetManager::get(uint16_t key) {
  auto it = hashMap.find(key);
  if (it != hashMap.end())
    return it->second;
  throw std::runtime_error(std::format(
      "RUNTIME ERROR: texture under key {} havent been loaded properly", key));
}

void AssetManager::init(uint16_t key, const char *assetPath) {
  AssetEntry asset{
      sf::Texture{sf::Texture{std::format("resources/{}", assetPath)}},
      {24, 32}, // TODO: read data of texture to get these
      {1}};
  hashMap.emplace(key, asset);
}
void AssetManager::initManager(uint32_t size) { hashMap.reserve(size); }
