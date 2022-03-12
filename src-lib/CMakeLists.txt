add_library(MainLib)

target_include_directories(MainLib PUBLIC api)

target_sources(
    MainLib PRIVATE 
        MyComplex.cpp demonstrate_misc.cpp demonstrate_templates.cpp
)
