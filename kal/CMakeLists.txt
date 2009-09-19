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
)

kde4_add_library(kal SHARED ${kal_LIB_SRCS})
set_target_properties(kal PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kal 
${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_PHONON_LIBS}
  ${OPENAL_LIBRARY} ${ALUT_LIBRARY}
    ${SNDFILE_LIBRARY} ${OGG_LIBRARY} ${VORBISFILE_LIBRARY})

add_subdirectory(includes)

install(TARGETS kal ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
kalbuffer.h
kalengine.h
kalsoundreader.h
kalengine_export.h
kalphonon.h
kalsound.h
kalmusic.h
kalcapture.h
widgets/kalinfowidget.h
widgets/kalplayerwidget.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kal COMPONENT Devel)
