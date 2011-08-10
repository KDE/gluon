cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
    find_package(GluonInput REQUIRED)
endif()

find_package(Qt4 4.7 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                    ${GLUON_GRAPHICS_INCLUDES}
                    ${GLUON_INPUT_INCLUDES})

set(uimanagercomponent_SRCS
    textureimageprovider.cpp
    uimanagercomponent.cpp
    engineaccess.cpp
    renderablescene.cpp

    uiasset.cpp
)

qt4_automoc(${uimanagercomponent_SRCS})
add_library(gluon_component_uimanager SHARED ${uimanagercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_uimanager GluonEngine GluonGraphics GluonInput)
endif()

set_target_properties(gluon_component_uimanager PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING}  DEFINE_SYMBOL MAKE_GLUON_COMPONENT_UIMANAGER_LIB)
target_link_libraries(gluon_component_uimanager GluonEngine ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${QT_QTDECLARATIVE_LIBRARY})

install(
    TARGETS
    gluon_component_uimanager
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(FILES template.qml DESTINATION ${SHARE_INSTALL_DIR}/gluon/templates/ui)
