add_library(entity STATIC entity.cpp player.cpp)
target_link_libraries(entity PUBLIC engine)
target_include_directories(entity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
