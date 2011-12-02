include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(statisticscomponent_SRCS
    statisticscomponent.cpp
)

gluon_add_plugin(gluon_component_statistics ${statisticscomponent_SRCS})
target_link_libraries(gluon_component_statistics GluonEngine)

install(
    TARGETS
    gluon_component_statistics
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
