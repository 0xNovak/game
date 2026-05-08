#include "engine/renderer.h"

#include "engine/render_entries.h"
#include <algorithm>
#include <execution>
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
