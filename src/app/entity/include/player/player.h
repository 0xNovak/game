
#pragma once

#include "SFML/System/Vector2.hpp"
#include "entity.h"

#include <array>
#include <cstdint>
#include <limits>
#include <unordered_set>

#include "player/item.h"
#include "player/weapon.h"

namespace entity {
class Player : public Entity, public IMoving {

public:
  Player(Hitbox hitbox, uint16_t spriteId) : Entity(hitbox, spriteId) {};
  void handleInput();
  void updatePosition(float deltaTime) override;
  float invincibilityTLeft{0};

  void inventoryAddWeapon(item::weapon::IWeapon *weapon);
  void inventoryAddUsable(item::IUsable *weapon);
  void inventoryAddStackable(item::IStackable *weapon);

private:
  struct Roll {
    float cooldown{0.75f};
    float sinceLast{std::numeric_limits<float>::infinity()};
    sf::Vector2f direction{0.f, 0.f};
    float left{0};
    float duration{0.25f};
    float speedMultiplier{25};
  };
  struct Inventory {
    item::weapon::IWeapon *RHand{nullptr};
    item::weapon::IWeapon *OffHand{nullptr};
    std::array<item::weapon::IWeapon *, 30> weapons{};
    std::unordered_set<item::IStackable *> items{};
    std::unordered_map<item::IStackable *, item::IUsable *> usableItems{};
  };
  Roll roll_m{};
  Inventory inventory_m{};
};
} // namespace entity
