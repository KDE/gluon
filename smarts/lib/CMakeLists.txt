find_package(Qt5Xml REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

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
    btlib.h
    btnode.h
    probnode.h
    btprobselectornode.h
    btparallelnode.h

    btperception.h
    btperceptionviewcone.h
    btperceptioninfo.h
    btperceptionatom.h

    gluon_smarts_export.h
)

gluon_add_library(Gluon::Smarts SHARED 
    SOURCES ${GluonSmarts_SRCS}
    HEADERS ${GluonSmarts_HEADERS}
    INCLUDES ${Qt5_XML_INCLUDE_DIRS}
    LIBRARIES Qt5::Xml Gluon::Core
)

if(APPLE)
    set_target_properties(Gluon::Smarts PROPERTIES FRAMEWORK TRUE)
    set_target_properties(Gluon::Smarts PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(Gluon::Smarts PROPERTIES PUBLIC_HEADER "${GluonSmarts_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER smarts)
    set(MACOSX_FRAMEWORK_IDENTIFIER Gluon::Smarts)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
