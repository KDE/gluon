find_package( Qt5Network REQUIRED )

set( LIBATTICA_MIN_VERSION 0.1.90 )
find_package( KF5Attica REQUIRED )

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
    personslistjob.cpp
    personself.cpp
    personselfjob.cpp
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

gluon_add_library(Gluon::Player SHARED
    SOURCES ${GluonPlayer_SRCS}
    HEADERS ${GluonPlayer_HEADERS}
    INCLUDES ${LIBATTICA_INCLUDE_DIR} ${Qt5Network_INCLUDE_DIRS}
    LIBRARIES Gluon::Engine Qt5::Network KF5::Attica )

gluon_add_subdirectories( tests )

