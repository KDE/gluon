cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDE_DIRS})

set(statisticscomponent_SRCS
    statisticscomponent.cpp
)

qt4_automoc(${statisticscomponent_SRCS})
add_library(gluon_component_statistics SHARED ${statisticscomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_statistics GluonEngine)
endif()

set_target_properties(gluon_component_statistics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_STATISTICS_LIB)
target_link_libraries(gluon_component_statistics GluonEngine)

install(
    TARGETS
    gluon_component_statistics
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
