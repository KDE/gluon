include_directories(../)
include_directories(${EIGEN2_INCLUDE_DIR})

set(gluonproject_LIB_SRCS
    asset.cpp
    assetprivate.cpp
    component.cpp
    componentprivate.cpp
    gameobject.cpp
    gameobjectprivate.cpp
    prefab.cpp
    prefabprivate.cpp
    project.cpp
    projectprivate.cpp
)

qt4_automoc(${gluonproject_LIB_SRCS})

SET(gluonproject_RCCS
../../resources/resources.qrc
)

QT4_ADD_RESOURCES(gluonproject_RCC_SRCS ${gluonproject_RCCS})
kde4_add_library(gluonproject SHARED ${gluonproject_LIB_SRCS} ${gluonproject_RCC_SRCS})

set_target_properties(gluonproject PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)
target_link_libraries(gluonproject ${KDE4_KDEUI_LIBS})

install(TARGETS gluonproject ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    asset.h
    component.h
    gameobject.h
    prefab.h
    project.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon COMPONENT Devel)
