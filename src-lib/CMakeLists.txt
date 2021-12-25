add_library(MainLib)

target_include_directories(MainLib PUBLIC api)

target_sources(MainLib PRIVATE MyTypes.cpp)
