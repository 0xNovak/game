#include "entity/player.h"
#include "entity.h"
#include "log.h"

#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
using entity::Player;

void Player::handleInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    direction.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    direction.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    direction.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    direction.x += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
      roll_m.cooldown <= roll_m.sinceLast)
    roll_m.left = roll_m.duration;
}
void Player::updatePosition(float dt) {
  if (roll_m.cooldown >= roll_m.sinceLast) {
    roll_m.sinceLast += dt;
    Log::debug(std::format("lastroll = {}", roll_m.sinceLast));
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
