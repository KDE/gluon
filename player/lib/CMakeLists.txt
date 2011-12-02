set(LIBATTICA_MIN_VERSION 0.1.90)
find_package(LibAttica)

set(libGluonPlayer_SRCS
    abstractjob.cpp
    abstractsocialservicesjob.cpp
    addgamejob.cpp

    archive/archiver.cpp
    archive/extractor.cpp

    atticamanager.cpp
    categorylistjob.cpp
    commentslistjob.cpp
    commentuploadjob.cpp
    editgamejob.cpp
    gamedetailitem.cpp
    gamedetailsjob.cpp
    gamedetaillistjob.cpp
    gamedownloadjob.cpp
    gameuploadjob.cpp
    licensejob.cpp
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

gluon_include_directories(${GLUONGRAPHICS_INCLUDES} ${GLUONENGINE_INCLUDES} ${LIBATTICA_INCLUDE_DIR})
gluon_add_library(GluonPlayer SHARED ${libGluonPlayer_SRCS})
gluon_target_link_libraries(GluonPlayer
    ${LIBATTICA_LIBRARIES}
    ${GLUONCORE_LIBRARIES}
    ${GLUONENGINE_LIBRARIES}
    ${QT_QTNETWORK_LIBRARY}
)

install(
    TARGETS     GluonPlayer
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonplayer
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonplayer
)

install(FILES
    atticamanager.h

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

