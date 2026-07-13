add_library(
  app
  STATIC
  app.cpp
  entity.cpp
  entity/player.cpp
)
target_link_libraries(app PUBLIC engine utility)
target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
