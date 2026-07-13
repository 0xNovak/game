#pragma once
#include "SFML/System/Vector2.hpp"

using namespace sf;
template <typename T1, typename T2>
T1 operator*(const Vector2<T1> &first, const Vector2<T2> &second) {
  T1 X = first.x * second.x;
  T1 Y = first.y * second.y;
  return {X, Y};
}
template <typename T1, typename T2>
Vector2f operator/(const Vector2<T1> &first, const Vector2<T2> &second) {
  auto X = static_cast<float>(first.x) / second.x;
  auto Y = static_cast<float>(first.y) / second.y;
  return {X, Y};
}
