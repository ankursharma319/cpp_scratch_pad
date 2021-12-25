
# add the executable
add_executable(MainExe ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(MainExe MainLib)

install(TARGETS MainExe)
