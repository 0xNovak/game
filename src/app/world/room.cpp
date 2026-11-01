#include "room.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <stdexcept>
#include <string>

#include <log.h>
#include <ussableInt.h>
#include <vector>

using namespace world;
void logBasicInfo(Room room);
Room getRoom(const char *path) {
  auto roomPath =
      std::filesystem::path("resources/rooms") / std::filesystem::path(path);
  if (!std::filesystem::is_regular_file(roomPath)) {
    std::string msg = std::string("room ") + path +
                      " was not found\n   path: " + roomPath.string();
    throw std::runtime_error(msg);
  }

  std::ifstream roomFile(roomPath, std::ios::binary);
  if (!roomFile) {
    std::string msg = std::string("room ") + path + " was not opened correctly";
    throw std::runtime_error(msg);
  }

  u16 shape;
  roomFile.read(reinterpret_cast<char *>(&shape), 2);
  u8 totalRoomTiles;
  roomFile.read(reinterpret_cast<char *>(&totalRoomTiles), 1);

  std::vector<RoomTile> tiles;
  tiles.reserve(totalRoomTiles);
  for (u8 i = 0; i < totalRoomTiles; ++i) {
    RoomTile read;
    roomFile.read(reinterpret_cast<char *>(&read), sizeof(RoomTile));
    tiles.push_back(read);
  }

  u8 totalEntities;
  roomFile.read(reinterpret_cast<char *>(&totalEntities), 1);

  std::vector<EntityRData> entities;
  entities.reserve(totalEntities);
  for (u8 i = 0; i < totalEntities; ++i) {
    EntityRData read;
    roomFile.read(reinterpret_cast<char *>(&read), sizeof(EntityRData));
    entities.push_back(read);
  }
  bool rotable;
  roomFile.read(reinterpret_cast<char *>(&rotable), 1);
  roomFile.close();
  auto room = Room{
      .shape = shape,
      .rotable = rotable,
      .roomTiles = std::move(tiles),
      .entities = std::move(entities),
  };
  logBasicInfo(room);
  return room;
}

void logBasicInfo(Room room) {
  Log::debug(std::format("room shape: {:016b}", room.shape));
  Log::debug(std::format("room total room tiles: {}", room.roomTiles.size()));
  Log::debug(std::format("room total entities: {}", room.entities.size()));
}
