include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(qtquickasset_SRCS
    qtquickasset.cpp
)

qt4_automoc(${qtquickasset_SRCS})
add_library(gluon_asset_qtquick SHARED ${qtquickasset_SRCS})

set_target_properties(gluon_asset_qtquick PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_QTQUICK_LIB)
target_link_libraries(gluon_asset_qtquick GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_qtquick
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
