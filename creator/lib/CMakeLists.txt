set(gluoncreatorlib_SRCS
    dockplugin.cpp
    dockpluginloader.cpp
)

qt4_automoc(${gluoncreatorlib_SRCS})
add_library(gluoncreatorlib SHARED ${gluoncreatorlib_SRCS})
set_target_properties(gluoncreatorlib PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} DEFINE_SYMBOL "MAKE_GLUONCREATOR_LIB")
target_link_libraries(gluoncreatorlib ${GLUON_LIBRARY} ${KDE4_KDEUI_LIBS})

##### INSTALL #####

add_subdirectory(cmake)

install(TARGETS gluoncreatorlib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/gluon/creator)
install(FILES
        gluoncreator_macros.h
        dockplugin.h
        dockpluginloader.h
        gluoncreatorlib_export.h
        DESTINATION ${INCLUDE_INSTALL_DIR}
)
