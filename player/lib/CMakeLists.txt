set(LIBATTICA_MIN_VERSION 0.1.90)

find_package(LibAttica)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_GRAPHICS_INCLUDES}
    ${GLUON_ENGINE_INCLUDES}
    ${LIBATTICA_INCLUDE_DIR}
)

set(GLUON_PLAYER_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_GRAPHICS_INCLUDES}
    ${GLUON_ENGINE_INCLUDES}
    ${LIBATTICA_INCLUDE_DIR}
    CACHE INTERNAL "Include files required for Gluon Player"
)

set(libGluonPlayer_SRCS
    abstractjob.cpp
    addgamejob.cpp
    atticamanager.cpp
    authentication.cpp
    categorylistjob.cpp
    commentlistjob.cpp
    gamecontentjob.cpp
    gamedetaillistjob.cpp
    ratingjob.cpp
    serviceprovider.cpp

    archive/archive.cpp

    models/gameviewitem.cpp
    models/gameitemsmodel.cpp
    models/commentitemsmodel.cpp
    models/commentsmodel.cpp
    models/highscoresmodel.cpp
)

qt4_automoc(${libGluonPlayer_SRCS})
add_library(libGluonPlayer SHARED ${libGluonPlayer_SRCS})
set_target_properties(libGluonPlayer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_PLAYER_LIB PREFIX "")

target_link_libraries(libGluonPlayer
    ${LIBATTICA_LIBRARIES}
    ${GLUON_CORE_LIBS}
    ${GLUON_ENGINE_LIBS}
    ${QT_QTNETWORK_LIBRARY}
)

set(GLUON_PLAYER_LIBS
    libGluonPlayer
    ${LIBATTICA_LIBRARIES}
    ${GLUON_CORE_LIBS}
    ${GLUON_ENGINE_LIBS}
    ${QT_QTNETWORK_LIBRARY}
    CACHE INTERNAL "Libraries required for Gluon Player"
)

install(
    TARGETS libGluonPlayer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)

install(FILES
    atticamanager.h
    authentication.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/player/lib
    COMPONENT Devel
)

install(FILES
    archive.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/player/lib/archive
    COMPONENT Devel
)

install(FILES
    models/commentitemsmodel.h
    models/gameitemsmodel.h
    models/highscoresmodel.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/player/lib/models
    COMPONENT Devel
)
