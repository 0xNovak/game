add_library(
  engine
  STATIC
  engine.cpp
  renderer.cpp
)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(engine PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
