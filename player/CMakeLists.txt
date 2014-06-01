set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

set( LIBATTICA_MIN_VERSION 0.1.90 )
find_package( KF5Attica )
find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Qml REQUIRED )
find_package( Qt5Quick REQUIRED )

gluon_include_directories( GluonPlayer
    ${GLUONENGINE_INCLUDES}
    ${LIBATTICA_INCLUDE_DIR}
)

set(GluonPlayer_SRCS
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
    gamemanager.cpp
    gamemetadata.cpp
    gameuploadjob.cpp
    licensejob.cpp
    ratingjob.cpp
    serviceprovider.cpp

    models/achievementsmodel.cpp
    models/allgameitemsmodel.cpp
    models/commentitemsmodel.cpp
    models/downloadablegamesmodel.cpp
    models/gameitem.cpp
    models/gameitemsmodel.cpp
    models/gameviewitem.cpp
    models/highscoresmodel.cpp
    models/installedgamesmodel.cpp
)

set(GluonPlayer_HEADERS
    atticamanager.h
    models/achievementsmodel.h
    models/commentitemsmodel.h
    models/gameitemsmodel.h
    models/highscoresmodel.h
)

gluon_add_library(GluonPlayer SHARED
    SOURCES ${GluonPlayer_SRCS}
    HEADERS ${GluonPlayer_HEADERS}
    LIBRARIES ${GLUONENGINE_LIBRARIES} Qt5::Core Qt5::Qml Qt5::Gui Qt5::Quick KF5::Attica ${QT_QTNETWORK_LIBRARY} )

gluon_add_subdirectories( tests )

