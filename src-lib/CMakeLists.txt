add_library(MainLib)

target_include_directories(MainLib PUBLIC api)

target_sources(
    MainLib PRIVATE 
        MyComplex.cpp demonstrate_misc.cpp demonstrate_templates.cpp
        avl_tree.cpp string_algos.cpp big_math.cpp graph.cpp
        algo_practice.cpp
)
