#pragma once
#include <optional>
#include <unordered_map>
#include <ussableInt.h>
#include <utility>

#include <room.hpp>

namespace world {
struct PlacedRoom {
  i16 x, y;
  u16 id;
  u64 shapeMask;
}; // placeholder
struct RoomManager {
  const Room &get(u16 key);
  void init(u16 key, const char *roomPath);
  void initManager(u16 size);
  void clearCache();

private:
  // OPTIMALIZATION: could use specialized hash for ensuring 0
  // conflicts (bucketless)
  std::unordered_map<u16, Room> roomCache{};
};

struct MapManager {
  MapManager(RoomManager &RM) : RoomMan(RM) {};
  void init(u32 seed) { this->seed = seed; };
  void generateMap(u8 floorLevel);

  static const u8 W{8};
  static const u8 H{8};
  std::vector<PlacedRoom> placedRooms;
  u64 macrogrid{0}; // W*H = 64 bits
  u64 holesgrid{0}; // macrogrid tracking holes
  u32 seed;

private:
  bool try_place(u16 room_key, const u64 c);
  std::optional<u64> fit(u64 shape, i32 cx, i32 cy);
  u64 transformShape(u16 shape);
  bool boundsCheck(u64 shape, i32 cx, i32 cy);
  std::pair<i8, i8> findOffset(u64 shape, i32 cx, i32 cy, const u64 &c);
  u16 rotate90(u16 shape);
  RoomManager &RoomMan;
};

} // namespace world
