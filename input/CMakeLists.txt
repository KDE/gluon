cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonInput)
    find_package(GluonCore REQUIRED)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_CORE_INCLUDES}
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(APPLE)
    set(GLUON_INPUT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/mac
        CACHE PATHS "Includes required for Gluon Input"
    )

    find_library(IOKIT_LIBRARY NAMES IOKit)
    message("-- Found IOKit:" ${IOKIT_LIBRARY})

    find_library(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
    message("-- Found CoreFoundation:" ${COREFOUNDATION_LIBRARY})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mac/)
elseif(WIN32)
    set(GLUON_INPUT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/win
        ${GLUON_CORE_INCLUDES}
        CACHE PATHS "Includes required for Gluon Input"
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/)
else()
    set(GLUON_INPUT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/linux
        ${GLUON_CORE_INCLUDES}
        CACHE PATHS "Includes required for Gluon Input"
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux/)
endif()

###############win source and headers###################
set(GluonInput_SRCS_WIN )

set(GluonInput_HEADERS_WIN )
###############win source and headers###################

###############mac source and headers###################
set(GluonInput_SRCS_MAC
	mac/inputthread.cpp
	mac/inputthreadprivate.cpp
    mac/detectmac.cpp
	mac/detectmacprivate.cpp
	mac/gluonbuttons.cpp
	mac/inputevent.cpp
	mac/inputeventprivate.cpp
)

set(GluonInput_HEADERS_MAC
    mac/detectmac.h
	mac/inputthread.h
    mac/gluonbuttons.h
	mac/gluondevices.h
)
###############mac source and headers###################

###############linux source and headers###################
set(GluonInput_SRCS_LINUX
	linux/inputthread.cpp
	linux/inputthreadprivate.cpp
    linux/detectlinux.cpp
	linux/detectlinuxprivate.cpp
	linux/gluonbuttons.cpp
)

set(GluonInput_HEADERS_LINUX
	linux/inputthread.h
    linux/detectlinux.h
    linux/gluonbuttons.h
	linux/gluondevices.h
)
###############linux source and headers###################

###############common source and headers###################
set(GluonInput_SRCS_COMMON
    inputdevice.cpp
	inputdeviceprivate.cpp
    mouse.cpp
	mouseprivate.cpp
    tablet.cpp
	tabletprivate.cpp
    keyboard.cpp
	keyboardprivate.cpp
    joystick.cpp
	joystickprivate.cpp
    custominput.cpp
	custominputprivate.cpp
    inputmanager.cpp
	inputmanagerprivate.cpp
    detect.cpp
	inputbuffer.cpp
	inputbufferprivate.cpp
)

set(GluonInput_HEADERS_COMMON
    gluon_input_export.h
    inputmanager.h
    inputdevice.h
    mouse.h
    tablet.h
    keyboard.h
    joystick.h
    custominput.h
	detect.h
	absval.h
	inputbuffer.h
)
###############common source and headers###################

qt4_automoc(${GluonInput_SRCS_COMMON})

if(APPLE)
    qt4_automoc(${GluonInput_SRCS_MAC})
    add_library(GluonInput SHARED ${GluonInput_SRCS_MAC} ${GluonInput_SRCS_COMMON})
elseif(WIN32)
    qt4_automoc(${GluonInput_SRCS_WIN})
    add_library(GluonInput SHARED ${GluonInput_SRCS_WIN} ${GluonInput_SRCS_COMMON})
else()
    qt4_automoc(${GluonInput_SRCS_LINUX})
    add_library(GluonInput SHARED ${GluonInput_SRCS_LINUX} ${GluonInput_SRCS_COMMON})
endif()

set_target_properties(GluonInput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
if(GLUON_BUILD_ALL)
    add_dependencies(GluonInput GluonCore)
endif()

target_link_libraries(GluonInput ${GLUON_CORE_LIBS})

set(GLUON_INPUT_LIBS
    GluonInput
    ${GLUON_CORE_LIBS}
    CACHE PATHS "Libraries required for Gluon Input"
)

if(APPLE)
    set(GLUON_INPUT_LIBS
        ${GLUON_INPUT_LIBS}
        ${IOKIT_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
        CACHE PATHS "Libraries required for Gluon Input"
    )
elseif(WIN32)
else()
endif()

if(APPLE)
    target_link_libraries(GluonInput ${IOKIT_LIBRARY}  ${COREFOUNDATION_LIBRARY})
elseif(WIN32)
else()
endif()

install(TARGETS GluonInput DESTINATION ${LIB_INSTALL_DIR})

if(APPLE)
    install(
        FILES
        ${GluonInput_HEADERS_MAC}
        ${GluonInput_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
elseif(WIN32)
    install(
        FILES
        ${GluonInput_HEADERS_WIN}
        ${GluonInput_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
else()
    install(
        FILES
        ${GluonInput_HEADERS_LINUX}
        ${GluonInput_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
endif()
