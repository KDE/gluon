project(BehaviorTrees)

cmake_minimum_required(VERSION 2.6)

add_subdirectory(common)

if(BUILD_GLUON_SMARTS_EDITOR)
add_subdirectory(editor)
endif(BUILD_GLUON_SMARTS_EDITOR)

add_subdirectory(lib)


