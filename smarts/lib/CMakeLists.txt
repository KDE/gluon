project(btlib)
cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

set(_Init_LIB_SUFFIX "")
if ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
   set(_Init_LIB_SUFFIX 64)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
if ("${QT_QTCORE_LIBRARY}" MATCHES lib32)
   set(_Init_LIB_SUFFIX 32)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib32)

set(LIB_SUFFIX		    ${_Init_LIB_SUFFIX} CACHE STRING "The suffix of the system-wide library path")
set(LIB_INSTALL_DIR         ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}    CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed.")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../common/)

set(btlib_SRCS
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
	
	#main.cpp
)


set(btlib_HEADERS
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

add_definitions(-DMAKE_BT_LIB)

qt4_automoc(${btlib_SRCS})

if(APPLE)
	#add_executable(btlib ${btlib_SRCS} ${btlib_HEADERS})
	add_library(btlib SHARED ${btlib_SRCS} ${btlib_HEADERS})#${btlib_UIS_H})
	
	set_target_properties(btlib PROPERTIES FRAMEWORK TRUE)
	set_target_properties(btlib PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
	set_target_properties(btlib PROPERTIES PUBLIC_HEADER "${btlib_HEADERS}")
	
	add_custom_command(TARGET btlib POST_BUILD
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/SMARTS.framework/Headers/smarts/
		COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/SMARTS.framework/Headers/*.h ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/SMARTS.framework/Headers/smarts/
	)
	
	set(MACOSX_FRAMEWORK_IDENTIFIER SMARTS)
	set_target_properties(btlib PROPERTIES OUTPUT_NAME SMARTS)
else()
	add_library(btlib SHARED ${btlib_SRCS} )#${btlib_UIS_H})
endif()

set_target_properties(btlib PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_SMARTS_LIB)

target_link_libraries(btlib ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})

set(GLUON_SMARTS_LIBS
    btlib
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTXML_LIBRARY}
    CACHE INTERNAL "Libraries required for Gluon Smarts"
)

install(
    TARGETS btlib
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonsmarts
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonsmarts
)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/gluon/smarts)

install(FILES
    ${btlib_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}
    COMPONENT gluonsmarts
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

