include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/
)

set(GluonSmarts_SRCS
	btcharacter.cpp
    btfactory.cpp
    btbrain.cpp
    btselectornode.cpp
    btsequencenode.cpp
	btnode.cpp
	btprobselectornode.cpp
	btparallelnode.cpp

    btperception.cpp
    btperceptionviewcone.cpp
    btperceptioninfo.cpp
    btperceptionatom.cpp
)


set(GluonSmarts_HEADERS
	btcharacter.h
    btfactory.h
    btbrain.h
    btselectornode.h
    btsequencenode.h
    ../common/btglobal.h
    btlib_export.h
    btlib.h
	btnode.h
	probnode.h
	btprobselectornode.h
	btparallelnode.h

    btperception.h
    btperceptionviewcone.h
    btperceptioninfo.h
    btperceptionatom.h
)

qt4_automoc(${GluonSmarts_SRCS})

if(APPLE)
    add_library(GluonSmarts SHARED ${GluonSmarts_SRCS} ${GluonSmarts_HEADERS})
else()
    add_library(GluonSmarts SHARED ${GluonSmarts_SRCS})
endif()

if(APPLE)
    list(APPEND GluonSmarts_HEADERS
        ${GluonSmarts_HEADERS}
    )

    set_target_properties(GluonSmarts PROPERTIES FRAMEWORK TRUE)
	set_target_properties(GluonSmarts PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonSmarts PROPERTIES PUBLIC_HEADER "${GluonSmarts_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER smarts)
    set(MACOSX_FRAMEWORK_IDENTIFIER GluonSmarts)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

set_target_properties(GluonSmarts PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_SMARTS_LIB)

target_link_libraries(GluonSmarts ${GLUON_CORE_LIBS} ${QT_QTXML_LIBRARY})

set(GLUON_SMARTS_LIBS
    GluonSmarts
    ${GLUON_CORE_LIBS}
    ${QT_QTXML_LIBRARY}
    CACHE INTERNAL "Libraries required for Gluon Smarts"
)

install(
    TARGETS GluonSmarts
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonsmarts
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
)

install(FILES
    ${GluonSmarts_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/smarts
    COMPONENT gluonsmarts
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

