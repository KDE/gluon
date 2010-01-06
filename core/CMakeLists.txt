if(APPLE OR WIN32)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
endif()

install(FILES
    ksingleton.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/common COMPONENT Devel
)
