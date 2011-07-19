cmake_minimum_required(VERSION 2.8)

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
        CACHE INTERNAL "Includes required for Gluon Input"
    )

    find_library(IOKIT_LIBRARY NAMES IOKit)
    message("-- Found IOKit:" ${IOKIT_LIBRARY})

    find_library(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
    message("-- Found CoreFoundation:" ${COREFOUNDATION_LIBRARY})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mac/)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/qt/)
elseif(WIN32)
    set(GLUON_INPUT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/win
        ${GLUON_CORE_INCLUDES}
        CACHE INTERNAL "Includes required for Gluon Input"
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/qt/)
elseif(UNIX)
    set(GLUON_INPUT_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/linux
        ${GLUON_CORE_INCLUDES}
        CACHE INTERNAL "Includes required for Gluon Input"
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux/)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/qt/)
endif()

###############win source and headers###################
set(GluonInput_SRCS_WIN
    win/detectwin.cpp
    win/gluonbuttons.cpp
    win/inputthread.cpp
)

set(GluonInput_HEADERS_WIN
    win/detectwin.h
    win/gluonbuttons.h
    win/gluondevices.h
    win/inputthread.h
)
###############win source and headers###################

###############mac source and headers###################
set(GluonInput_SRCS_MAC
    mac/detectmac.cpp
    mac/gluonbuttons.cpp
    mac/inputthread.cpp
    mac/inputthread_p.cpp
)

set(GluonInput_HEADERS_MAC
    mac/detectmac.h
    mac/gluonbuttons.h
    mac/gluondevices.h
    mac/inputthread.h
)
###############mac source and headers###################

###############linux source and headers###################
set(GluonInput_SRCS_LINUX
    linux/detectlinux.cpp
    linux/detectlinux_p.cpp
    linux/gluonbuttons.cpp
    linux/inputthread.cpp
    linux/inputthread_p.cpp
)

set(GluonInput_HEADERS_LINUX
    linux/detectlinux.h
    linux/gluonbuttons.h
    linux/gluondevices.h
    linux/inputthread.h
)
###############linux source and headers###################

###############qt source and headers###################
set(GluonInput_SRCS_QT
    qt/detectqt.cpp
    qt/detectqt_p.cpp
    qt/gluonqtbuttons.cpp
)

set(GluonInput_HEADERS_QT
    qt/detectqt.h
    qt/gluonqtbuttons.h
    qt/gluonqtdevices.h
)
###############qt source and headers###################

###############common source and headers###################
set(GluonInput_SRCS_COMMON
    custominput.cpp
    custominput_p.cpp
    detect.cpp
    inputbuffer.cpp
    inputbuffer_p.cpp
    inputmanager.cpp
    inputmanager_p.cpp
    joystick.cpp
    joystick_p.cpp
    keyboard.cpp
    keyboard_p.cpp
    inputdevice.cpp
    inputdevice_p.cpp
    mouse.cpp
    mouse_p.cpp
    touch.cpp
    touch_p.cpp
)

set(GluonInput_HEADERS_COMMON
    absval.h
    custominput.h
    detect.h
    gluon_input_export.h
    inputbuffer.h
    inputdevice.h
    inputmanager.h
    joystick.h
    keyboard.h
    mouse.h
    touch.h
)
###############common source and headers###################

qt4_automoc(${GluonInput_SRCS_COMMON})
qt4_automoc(${GluonInput_SRCS_QT})

if(APPLE)
    qt4_automoc(${GluonInput_SRCS_MAC})
    add_library(GluonInput SHARED ${GluonInput_SRCS_MAC} ${GluonInput_SRCS_COMMON} ${GluonInput_HEADERS_COMMON} ${GluonInput_HEADERS_MAC} ${GluonInput_SRCS_QT})
elseif(WIN32)
    qt4_automoc(${GluonInput_SRCS_WIN})
    add_library(GluonInput SHARED ${GluonInput_SRCS_WIN} ${GluonInput_SRCS_QT} ${GluonInput_SRCS_COMMON})
elseif(UNIX)
    qt4_automoc(${GluonInput_SRCS_LINUX})
    add_library(GluonInput SHARED ${GluonInput_SRCS_LINUX} ${GluonInput_SRCS_QT} ${GluonInput_SRCS_COMMON})
endif()


set_target_properties(GluonInput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_INPUT_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND ${GluonInput_HEADERS_COMMON}
            GluonInput_HEADERS_COMMON
    )
    list(APPEND ${GluonInput_HEADERS_MAC}
            GluonInput_HEADERS_MAC
    )

    set_target_properties(GluonInput PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonInput PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonInput PROPERTIES PUBLIC_HEADER "${GluonInput_HEADERS_COMMON} ${GluonInput_HEADERS_MAC}")

    set(MACOSX_FRAMEWORK_IDENTIFIER input)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()


target_link_libraries(GluonInput ${GLUON_CORE_LIBS})

set(GLUON_INPUT_LIBS
    GluonInput
    ${GLUON_CORE_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Input"
)

if(APPLE)
    set(GLUON_INPUT_LIBS
        ${GLUON_INPUT_LIBS}
        ${IOKIT_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
        CACHE INTERNAL "Libraries required for Gluon Input"
    )
endif()

if(APPLE)
    target_link_libraries(GluonInput ${IOKIT_LIBRARY} ${COREFOUNDATION_LIBRARY})
endif()

install(
    TARGETS GluonInput
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    FRAMEWORK DESTINATION ${LIB_INSTALL_DIR}
)

if(APPLE)
    install(
        FILES
        ${GluonInput_HEADERS_COMMON}
        ${GluonInput_HEADERS_MAC}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
elseif(WIN32)
    install(
        FILES
        ${GluonInput_HEADERS_COMMON}
        ${GluonInput_HEADERS_WIN}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
elseif(UNIX)
    install(
        FILES
        ${GluonInput_HEADERS_COMMON}
        ${GluonInput_HEADERS_LINUX}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
endif()

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    FILES
    ${GluonInput_HEADERS_COMMON}
    ${GluonInput_HEADERS_QT}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/qt
    COMPONENT Devel
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
