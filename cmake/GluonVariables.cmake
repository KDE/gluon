if( NOT DEFINED ${GLUON_VERSION_STRING} )
    set( GLUON_VERSION_MAJOR 0 )
    set( GLUON_VERSION_MINOR 72 )
    set( GLUON_VERSION_PATCH 0 )
    set( GLUON_VERSION_STRING "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}" )
    set( GLUON_VERSION_NAME "Alpha Particle" )

    if( "${QT_QTCORE_LIBRARY}" MATCHES lib64 )
        set(LIB_SUFFIX 64)
    elseif( "${QT_QTCORE_LIBRARY}" MATCHES lib32 )
        set( LIB_SUFFIX 32) 
    endif( "${QT_QTCORE_LIBRARY}" MATCHES lib64 )

    set( BIN_INSTALL_DIR bin CACHE INTERNAL "The directory where binary files will be installed." )
    set( INCLUDE_INSTALL_DIR include CACHE INTERNAL "The directory where header files will be installed." )
    set( LIB_INSTALL_DIR lib${LIB_SUFFIX} CACHE INTERNAL "The directory where libraries will be installed." )
    set( SHARE_INSTALL_DIR share CACHE INTERNAL "The directory where data and other files will be installed." )
    set( DATA_INSTALL_DIR ${SHARE_INSTALL_DIR}/gluon CACHE INTERNAL "The directory where all of Gluon's data should be installed" )

    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        set( GLUON_ARCHITECTURE "64" )
    else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        set( GLUON_ARCHITECTURE "32" )
    endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/gluon_global.h.in ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h )
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h DESTINATION ${INCLUDE_INSTALL_DIR} )
endif( NOT DEFINED ${GLUON_VERSION_STRING} )
