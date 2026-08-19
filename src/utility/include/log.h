#pragma once
#include <exception>
#include <print>
#include <string_view>

// clang-format off
namespace TColor {
constexpr std::string_view red     = "\033[31m";
constexpr std::string_view green   = "\033[32m";
constexpr std::string_view yellow  = "\033[33m";
constexpr std::string_view blue    = "\033[34m";
constexpr std::string_view magenta = "\033[35m";
constexpr std::string_view cyan    = "\033[36m";
constexpr std::string_view reset   = "\033[0m";
} // Color
// clang-format on
namespace Log {
inline void err(std::string_view str) {
  std::println("[{}ERR{}] {}", TColor::red, TColor::reset, str);
}

inline void info(std::string_view str) {
  std::println("[{}LOG{}] {}", TColor::yellow, TColor::reset, str);
}

inline void debug(std::string_view str) {
#ifdef DEBUG_LOG
  std::println("[{}D LOG{}] {}", TColor::blue, TColor::reset, str);
#endif /* ifdef #ifdef DEBUG_LOG */
}
} // namespace Log
