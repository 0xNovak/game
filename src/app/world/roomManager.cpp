#include <cstdlib>
#include <worldManager.hpp>

#include <log.h>
#include <ussableInt.h>
using namespace world;
using RM = RoomManager;
const Room &RM::get(u16 key) {

  auto it = roomCache.find(key);
  if (it != roomCache.end()) [[likely]]
    return it->second;

  const std::string roomPath = std::format("{}.room", key);
  this->init(key, roomPath.c_str());

  auto it_RETRY = roomCache.find(key);
  if (it_RETRY != roomCache.end()) [[likely]]
    return it_RETRY->second;

  Log::err(std::format(
      "room under {} was requested but it wasnt able to load corecty"
      "properly, exiting..",
      key));
  exit(1);
}
void RM::init(u16 key, const char *roomPath) {
  roomCache.emplace(key, getRoom(roomPath));
}
void RM::initManager(u16 size) { roomCache.reserve(size); }

void RM::clearCache() { roomCache.clear(); }
