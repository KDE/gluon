
set( GluonInput_SRCS
#     axisparameter.cpp
#     buttonparameter.cpp
    inputaction.cpp
    inputparameter.cpp
    inputmanager.cpp
    inputdevice.cpp
)

set( GluonInput_HEADERS
#     axisparameter.h
#     buttonparameter.h
    inputaction.h
    inputparameter.h
    inputmanager.h
    deviceplugin.h
    inputdevice.h
    platformplugin.h
)

gluon_add_library( Gluon::Input SHARED
    SOURCES ${GluonInput_SRCS}
    HEADERS ${GluonInput_HEADERS}
    LIBRARIES Gluon::Core
)

add_subdirectory( qt )

gluon_add_subdirectories( examples tests )
