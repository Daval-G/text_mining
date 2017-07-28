set(TREE_SOURCES ${TREE_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/cptrie.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cptrie.hpp)

add_library(
    tree SHARED ${TREE_SOURCES}
        )
