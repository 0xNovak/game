add_subdirectory(engine)
add_executable(application main.cpp)
target_link_libraries(application engine)
