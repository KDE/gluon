set(gluoncreatorlib_SRCS
    plugin.cpp
    dockplugin.cpp
    pluginloader.cpp

    models/projectmodel.cpp
    models/scenemodel.cpp
    
    widgets/dock.cpp
)

qt4_automoc(${gluoncreatorlib_SRCS})
add_library(gluoncreatorlib SHARED ${gluoncreatorlib_SRCS})
set_target_properties(gluoncreatorlib PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} DEFINE_SYMBOL "MAKE_GLUONCREATOR_LIB")
target_link_libraries(gluoncreatorlib ${GLUON_LIBRARY} ${KDE4_KDEUI_LIBS})

##### INSTALL #####

add_subdirectory(cmake)

install(TARGETS gluoncreatorlib LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/gluon/creator)
install(FILES
        plugin.h
        dockplugin.h
        pluginloader.h
        gluoncreatorlib_macros.h
        DESTINATION ${INCLUDE_INSTALL_DIR}
)

install(FILES
        models/projectmodel.h
        models/scenemodel.h
        DESTINATION ${INCLUDE_INSTALL_DIR}/models
)

install(FILES
        widgets/dock.h
        DESTINATION ${INCLUDE_INSTALL_DIR}/widgets
)

install(FILES
        gluoncreator_plugin.desktop
        DESTINATION ${SERVICETYPES_INSTALL_DIR}
)
