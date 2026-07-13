add_library(
  utility
  STATIC
  util.cpp
)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(engine PRIVATE
    sfml-system
)
