include_directories(../lib)

set(GLUON_CREATOR_LIBS
    ${KDE4_KDEUI_LIBS}
    libGluonCreator
)

if(GLUON_BUILD_ALL)
    set(GLUON_CREATOR_LIBS
        ${GLUON_CREATOR_LIBS}
        GluonCore
        GluonEngine
    )
else()
    set(GLUON_CREATOR_LIBS
        ${GLUON_CREATOR_LIBS}
        ${GLUON_ENGINE_LIBS}
    )
endif()

add_subdirectory(docks)
#add_subdirectory(tools)
