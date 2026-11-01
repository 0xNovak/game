#pragma once
#include <cstdint>

#include "SFML/System/Angle.hpp"
#include "player/item.h"

namespace entity::item::weapon {
enum class type { direct, indirect };
struct IWeapon {
  virtual void use() = 0;
  enum class quality {
    common,
    rare,
    legendary,
    mithical
  }; // TODO:upgrade qualities
  quality quality{};
  float damage{};
  float range{};
};

struct IGun {
  struct ammunition {};
  struct Magazine {
    void reload();
    uint16_t capacity{};
    uint16_t bulletsLeft{};
    float reloadTime{};
    float reloadLeft{};
    ammunition ammution{}; // TODO:ammunition
  };

  float bulletImprecision{};
  Magazine mag{};
};
struct IMele {
  sf::Angle swingAngle{};
};
struct IWand {
  void *spell{}; // TODO:spells
};
} // namespace entity::item::weapon
