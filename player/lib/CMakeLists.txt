gluon_include_directories( GluonPlayer
    ${GLUON_ENGINE_INCLUDE_DIRS}
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
    LIBRARIES ${GLUONENGINE_LIBRARIES} ${QT_QTNETWORK_LIBRARY} ${LIBATTICA_LIBRARIES})

if(BUILD_GLUON_TESTS)
    add_subdirectory(tests)
endif()

