#pragma once
#include <cstdint>

namespace entity::item {
enum class ItemClass {
  weapon,
  utility,
  material,
};
struct Item {
  bool keyItem{false};
};
struct IStackable {
  uint16_t quantity{};
};
struct IUsable {
  virtual void use() = 0;
};
} // namespace entity::item
