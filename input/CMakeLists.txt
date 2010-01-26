cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonInput)
    find_package(GluonCore REQUIRED)
    include_directories(${GLUON_CORE_INCLUDES})
else(NOT GLUON_BUILD_ALL)
    include_directories(${QT_INCLUDES} ${EIGEN2_INCLUDE_DIR})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(WIN32)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/)
elseif(APPLE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mac/)
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux/)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

###############win source and headers###################
set(kcl_LIB_SRCS_WIN )

set(kcl_LIB_HEADERS_WIN )
###############win source and headers###################

###############mac source and headers###################
set(kcl_LIB_SRCS_MAC
    mac/inputevent.cpp
    mac/thread.cpp
    mac/input.cpp
    mac/mouse.cpp
    mac/tablet.cpp
    mac/keyboard.cpp
    mac/joystick.cpp
    mac/code.cpp
    mac/detectmac.cpp
    mac/custominput.cpp
)

set(kcl_LIB_HEADERS_MAC
    mac/gluoninput.h
    mac/inputevent.h
    mac/thread.h
    mac/input.h
    mac/mouse.h
    mac/tablet.h
    mac/keyboard.h
    mac/joystick.h
    mac/code.h
    mac/detectmac.h
    mac/custominput.h
)
###############mac source and headers###################

###############linux source and headers###################
set(kcl_LIB_SRCS_LINUX
    linux/inputevent.cpp
    linux/thread.cpp
    linux/input.cpp
    linux/mouse.cpp
    linux/tablet.cpp
    linux/keyboard.cpp
    linux/joystick.cpp
    linux/code.cpp
    linux/detectlinux.cpp
    linux/custominput.cpp
)

set(kcl_LIB_HEADERS_LINUX
    linux/gluoninput.h
    linux/inputevent.h
    linux/thread.h
    linux/input.h
    linux/mouse.h
    linux/tablet.h
    linux/keyboard.h
    linux/joystick.h
    linux/code.h
    linux/detectlinux.h
    linux/custominput.h
)
###############linux source and headers###################

###############common source and headers###################
set(kcl_LIB_SRCS_COMMON
    kcldetect.cpp
    common/kcldetectabstract.cpp

    #widgets/kclpressbutton.cpp
    #widgets/kclinputwidget.cpp
    #widgets/kclcustominputdialog.cpp
    #widgets/kclinfowidget.cpp
    #widgets/kcldevicemodel.cpp
)

set(kcl_LIB_HEADERS_COMMON
    gluon_input_export.h
    detect.h
)
###############common source and headers###################

qt4_automoc(${kcl_LIB_SRCS_COMMON})

IF(WIN32)
    qt4_automoc(${kcl_LIB_SRCS_WIN})
    add_library(kcl SHARED ${kcl_LIB_SRCS_WIN} ${kcl_LIB_SRCS_COMMON})
ELSEIF(APPLE)
    qt4_automoc(${kcl_LIB_SRCS_MAC})
    add_library(kcl SHARED ${kcl_LIB_SRCS_MAC} ${kcl_LIB_SRCS_COMMON})
ELSE()
    qt4_automoc(${kcl_LIB_SRCS_LINUX})
    add_library(kcl SHARED ${kcl_LIB_SRCS_LINUX} ${kcl_LIB_SRCS_COMMON})
ENDIF()

set_target_properties(kcl PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

target_link_libraries(kcl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

#TODO: Fix the library path stuff so that we install it into the correct directory
if(APPLE)
    target_link_libraries(kcl ${IOKIT_LIBRARY}  ${COREFOUNDATION_LIBRARY})
    install(TARGETS kcl DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
elseif(WIN32)
else()
    install(TARGETS kcl DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

if(APPLE)
    install(
        FILES
        ${kcl_LIB_HEADERS_MAC}
        ${kcl_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
elseif(WIN32)
    install(
        FILES
        ${kcl_LIB_HEADERS_WIN}
        ${kcl_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
else()
    install(
        FILES
        ${kcl_LIB_HEADERS_LINUX}
        ${kcl_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
endif()

install(
    FILES
    common/kcldetectabstract.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input/common
    COMPONENT Devel
)

install(


#install(FILES
#widgets/kclpressbutton.h
#widgets/kclinputwidget.h
#widgets/kclcustominputdialog.h
#widgets/kclinfowidget.h
#widgets/kcldevicemodel.h
#DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl/widgets COMPONENT Devel)

