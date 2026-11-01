#include "room.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <stdexcept>

static const u16 BaseSquare = 0b1100'1100'0000'0000;
using namespace world;
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <room_name>\n";
    return 1;
  }
  std::println("creating clean room ./resouces/rooms/{}", argv[1]);
  char answer;
  if (std::filesystem::exists(std::filesystem::path("resources/rooms") /
                              std::filesystem::path(argv[1]))) {
    std::print("room already exists, do you want to overwrite it? (y/n)\n->");
    std::cin >> answer;
    if (answer != 'y')
      return 1;
  }

  std::ofstream roomFile(std::filesystem::path("resources/rooms") /
                             std::filesystem::path(argv[1]),
                         std::ios::binary);
  u16 shape = BaseSquare;
  // 1100
  // 1100
  // 0000
  // 0000
  u8 totalRoomTiles = 4;

  roomFile.write(reinterpret_cast<char *>(&shape), 2);
  roomFile.write(reinterpret_cast<char *>(&totalRoomTiles), 1);

  world::Tile EmptyTile{1, 0};
  world::Tile WallTile{2, world::TileFlag::TileFullWall};

  world::RoomTile roomTile{};

  for (u8 y = 0; y < world::RoomTile::H; ++y) {
    for (u8 x = 0; x < world::RoomTile::W; ++x) {
      if (y == 0 || y == world::RoomTile::H || x == 0 ||
          x == world::RoomTile::W) {
        roomTile.tiles[y * world::RoomTile::W + x] = WallTile;
      } else {
        roomTile.tiles[y * world::RoomTile::W + x] = EmptyTile;
      }
    }
  } // idc for optimalizing ts >:3
  for (u8 i = 0; i < totalRoomTiles; ++i)
    roomFile.write(reinterpret_cast<char *>(&roomTile),
                   sizeof(world::RoomTile));
  u8 totalEntities = 0;
  roomFile.write(reinterpret_cast<char *>(&totalEntities), 1);
  bool rotable = false;
  roomFile.write(reinterpret_cast<char *>(&rotable), 1);
  roomFile.close();
  std::println("room ./resouces/rooms/{} created", argv[1]);

  return 0;
}
