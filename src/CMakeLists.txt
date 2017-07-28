set(TREE_SOURCES ${TREE_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/cptrie.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cptrie.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ptrie.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ptrie.cpp)

add_library(
    tree SHARED ${TREE_SOURCES}
        )
