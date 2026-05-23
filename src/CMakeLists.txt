add_subdirectory(engine)
add_subdirectory(app)

add_executable(application main.cpp)
target_link_libraries(application app engine)
