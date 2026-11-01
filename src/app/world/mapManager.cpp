#include <worldManager.hpp>

#include <cstdlib>
#include <log.h>
#include <ussableInt.h>
#include <utility>

#include "room.hpp"

using namespace world;
static constexpr u64 MSB = u64{1} << (MapManager::W * MapManager::H - 1);

void MapManager::generateMap(u8 floorLevel) {
  macrogrid = 0;
  holesgrid = 0;
  u64 c = MSB;
  while (c) {
    for (int i = 0; i < 4; ++i) {
      auto room = RoomMan.get(0);
      if (auto placed = try_place(room, c)) {
        macrogrid |= *placed;
        break;
      }
      if (i == 3)
        holesgrid |= c;
    }
    while (c) { // advance to the next free cell
      c >>= 1;
      if (!(c & macrogrid))
        break;
    }
  }
}
std::optional<u64> MapManager::try_place(const Room &room, const u64 c) {
  const int idx = std::countl_zero(c);
  const int cy = idx / W, cx = idx % W;

  u16 shape = room.shape;
  const int tries = room.rotable ? 4 : 1; // covers the non-rotable case too
  for (int i = 0; i < tries; ++i) {
    const u64 shape_t = transformShape(shape);
    auto [ox, oy] = findOffset(shape_t, cx, cy, c);
    if (auto moved = fit(shape_t, ox, oy))
      return moved;
    shape = rotate90(shape); // cumulative
  }
  return std::nullopt;
}
std::optional<u64> MapManager::fit(u64 shape, i32 cx, i32 cy) {
  if (!boundsCheck(shape, cx, cy))
    return std::nullopt;
  const int k = cy * W + cx; // may be negative
  const u64 moved = k >= 0 ? shape >> k : shape << -k;
  if (moved & macrogrid)
    return std::nullopt;
  return moved;
}

bool MapManager::boundsCheck(u64 shape, i32 cx, i32 cy) {
  if (shape == 0)
    return false; // "room without edge"

  int rmin = -1, rmax = -1;
  unsigned cols = 0; // OR of all rows: which columns are used

  for (int r = 0; r < 4; ++r) {
    if (unsigned row = static_cast<unsigned>((shape >> (W * (H - 1 - r))) &
                                             ((1u << W) - 1))) {
      if (rmin < 0)
        rmin = r;
      rmax = r;
      cols |= row;
    }
  }

  // column j <-> bit (W-1-j): highest set bit = leftmost column
  const int cmin = (W - 1) - (std::bit_width(cols) - 1);
  const int cmax = (W - 1) - std::countr_zero(cols);

  return cy + rmin >= 0 && cy + rmax < H && cx + cmin >= 0 && cx + cmax < W;
}
std::pair<i8, i8> MapManager::findOffset(u64 shape, i32 cx, i32 cy,
                                         const u64 &c) {
  for (u8 i = 0; i < 4; ++i) {
    for (u8 j = 0; j < 4; ++j) {
      if (shape & (MSB >> (i * W + j)))
        return std::pair<i8, i8>(cx - j, cy - i);
    }
  }
  auto msg = std::format(
      "no offset could be found for room shape expanded(u64):\n {}", shape);
  Log::err(msg);
  exit(2);
}
u64 MapManager::transformShape(u16 shape) {
  u64 out = 0;
  for (int r = 0; r < 4; ++r) {
    const u64 nib = (shape >> (12 - 4 * r)) & 0xF;
    out |= nib << (W * H - 4 - r * W); // r=0 -> bit 60 for 8x8
  }
  return out;
}

u16 MapManager::rotate90(u16 shape) {
  u16 out = 0;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (shape & (0x8000 >> (i * 4 + j)))  // old cell (i, j)
        out |= 0x8000 >> (j * 4 + (3 - i)); // new cell (j, 3-i)
  return out;
}
