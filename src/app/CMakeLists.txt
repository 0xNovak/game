add_library(app STATIC app.cpp)
add_subdirectory(entity)
target_link_libraries(app PUBLIC engine entity utility)
target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
