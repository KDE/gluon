set(distributiondock_SRCS
    distributiondock.cpp
    distributiondockplugin.cpp
)

qt5_wrap_ui(
    distributiondock_SRCS
    distributiondock.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

gluon_add_plugin(gluoncreator_dockplugin_distributiondock 
    MODULE Gluon::Creator
    SOURCES ${distributiondock_SRCS}
    LIBRARIES Gluon::Creator
)

install(FILES gluoncreator_dockplugin_distributiondock.desktop DESTINATION ${SERVICES_INSTALL_DIR})
