#include "entity/player.h"

#include <SFML/Window/Keyboard.hpp>
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
}
