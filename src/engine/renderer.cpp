#include "engine/renderer.h"

#include <algorithm>
#include <cstdint>
#include <format>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SFML/Graphics/Texture.hpp"

#include "engine/render_entries.h"
#include "logEngine.h"

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
std::unordered_set<uint16_t> seenErrorKeys;
const AssetEntry &AssetManager::get(uint16_t key) const {
  auto it = hashMap.find(key);
  if (it != hashMap.end()) [[likely]]
    return it->second;
  if (seenErrorKeys.insert(key).second) {
    LogEng::err(std::format(
        "texture under {} haven't been loaded properly, falling back to debug",
        key));
  }

  return hashMap.at(0);
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
