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
    abstractsocialservicesjob.cpp
    addgamejob.cpp
    atticamanager.cpp
    authentication.cpp
    categorylistjob.cpp
    commentslistjob.cpp
    commentuploadjob.cpp
    gamedetaillistjob.cpp
    gamedownloadjob.cpp
    gameuploadjob.cpp
    ratingjob.cpp
    serviceprovider.cpp

    models/achievementsmodel.cpp
    models/allgameitemsmodel.cpp
    models/commentitemsmodel.cpp
    models/commentsmodel.cpp
    models/downloadablegamesmodel.cpp
    models/gameitem.cpp
    models/gameitemsmodel.cpp
    models/gameviewitem.cpp
    models/highscoresmodel.cpp
    models/installedgamesmodel.cpp
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
    TARGETS     libGluonPlayer
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonplayer
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
)

install(FILES
    atticamanager.h
    authentication.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/player/lib
    COMPONENT gluonplayer
)

install(FILES
    models/achievementsmodel.h
    models/commentitemsmodel.h
    models/gameitemsmodel.h
    models/highscoresmodel.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/player/lib/models
    COMPONENT gluonplayer
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

