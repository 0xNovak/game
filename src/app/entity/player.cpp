#include "player/player.h"
#include "entity.h"

#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
using entity::Player;

void Player::handleInput() {
  using sf::Keyboard::isKeyPressed;
  using sf::Keyboard::Key;
  if (isKeyPressed(Key::W) || isKeyPressed(Key::Up))
    direction.y -= 1.f;
  if (isKeyPressed(Key::S) || isKeyPressed(Key::Down))
    direction.y += 1.f;
  if (isKeyPressed(Key::A) || isKeyPressed(Key::Left))
    direction.x -= 1.f;
  if (isKeyPressed(Key::D) | isKeyPressed(Key::Right))
    direction.x += 1.f;
  if (isKeyPressed(Key::Space) && roll_m.cooldown <= roll_m.sinceLast)
    roll_m.left = roll_m.duration;
}
void Player::updatePosition(float dt) {
  if (roll_m.cooldown >= roll_m.sinceLast) {
    roll_m.sinceLast += dt;
  }
  if (roll_m.left <= 0) {
    Entity::updatePosition(dt);
    return;
  }
  // first roll frame
  if (roll_m.left == roll_m.duration) {
    invincibilityTLeft = std::max(roll_m.left, invincibilityTLeft);
    roll_m.direction = direction;
    roll_m.sinceLast = 0;
  }

  // cancel if no direction
  // TODO:change to roll to mouse direction
  if (roll_m.direction == sf::Vector2f{0, 0}) {
    roll_m.left = 0;
    roll_m.sinceLast = roll_m.cooldown;
    return;
  }
  sf::Vector2f positionDelta;
  positionDelta = roll_m.direction.normalized() * speed_m * 2.f * dt;
  position_m += positionDelta;
  direction = {0, 0};
  roll_m.left -= dt;
}
