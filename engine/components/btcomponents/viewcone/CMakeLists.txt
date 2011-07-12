cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES})

set(viewconecomponent_SRCS
    viewcone.cpp
    viewconeprivate.cpp
)

qt4_automoc(${viewconecomponent_SRCS})
add_library(gluon_component_btviewcone SHARED ${viewconecomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_btviewcone GluonEngine)
endif()

set_target_properties(gluon_component_btviewcone PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_BTVIEWCONE_LIB)
target_link_libraries(gluon_component_btviewcone GluonEngine)

install(
    TARGETS
    gluon_component_btviewcone
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
 
