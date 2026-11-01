#pragma once
#include "SFML/System/Vector2.hpp"

#include <array>
#include <ussableInt.h>
#include <vector>

namespace world {
enum TileFlag : u8 {
  TileObstacle = 1 << 0,
  TileDoor = 1 << 1,
  TileBlastproof = 1 << 2,
  TileWeakWall = 1 << 3,
  TileContactDamage = 1 << 4,

  TileFullWall = TileWeakWall | TileBlastproof, // blastproof wall quick binding
};
struct Tile {
  u16 textureID;
  u8 flag;
};
struct EntityRData {
  sf::Vector2f position;
  u16 entityID;
  u8 roomTileIndex;
};
struct RoomTile {
  static const u8 W{60}; // amount of tiles on x (1440p/24)
  static const u8 H{45}; // amount of tiles on y (1080p/24)
  std::array<Tile, W * H> tiles;
};
struct Room {
  u16 shape; // *1
  std::vector<RoomTile> roomTiles;
  std::vector<EntityRData> entities;
  bool rotable;
};
[[nodiscard]] Room getRoom(const char *path);
} // namespace world

//
// *1 shape is essentialy 4*4 matix of bits, 1-roomtile is acctive 0-its not
// -- example --
// [
//   1 1 1 0
//   0 1 0 0
//   0 1 0 0
//   0 0 0 0
// ] <- this one would be coded as 58432(u16) into decimal
// ^
// creates room with shape of leter T
