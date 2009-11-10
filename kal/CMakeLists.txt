cmake_minimum_required(VERSION 2.6)

find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(OggVorbis REQUIRED)

include_directories(${OPENAL_INCLUDE_DIR})

include_directories(${SNDFILE_INCLUDE_DIR}
                    ${OGG_INCLUDE_DIR}
                    ${VORBISFILE_INCLUDE_DIR})
include_directories(./)

set(kal_LIB_SRCS
    kalengine.cpp
    kalphonon.cpp
    kalsoundreader.cpp
    kalmusic.cpp
    kalcapture.cpp
    kalbuffer.cpp
    kalsound.cpp

    widgets/kalinfowidget.cpp
    widgets/kalplayerwidget.cpp

    kalcapturedevice_p.cpp
    kaldevice_p.cpp
)

qt4_automoc(${kal_LIB_SRCS})
add_library(kal SHARED ${kal_LIB_SRCS})

set_target_properties(kal PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

#${ALUT_INCLUDE_DIR}

target_link_libraries(kal
                      ${KDE4_PHONON_LIBS}
                      ${OPENAL_LIBRARY}
                      ${SNDFILE_LIBRARY}
                      ${OGG_LIBRARY}
                      ${VORBISFILE_LIBRARY}
		      ${PHONON_LIBRARY}
		${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
)

#${ALUT_LIBRARY}

add_subdirectory(includes)

if(APPLE)

install(TARGETS kal DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

else()

install(TARGETS kal ${INSTALL_TARGETS_DEFAULT_ARGS} )

endif()

install(FILES
kalbuffer.h
kalengine.h
kalsoundreader.h
kal_export.h
kalphonon.h
kalsound.h
kalmusic.h
kalcapture.h
widgets/kalinfowidget.h
widgets/kalplayerwidget.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kal COMPONENT Devel)

install(FILES
widgets/kalinfowidget.h
widgets/kalplayerwidget.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kal/widgets COMPONENT Devel)
