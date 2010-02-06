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
    find_library(IOKIT_LIBRARY NAMES IOKit)
    message("-- Found IOKit:" ${IOKIT_LIBRARY})

    find_library(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
    message("-- Found CoreFoundation:" ${COREFOUNDATION_LIBRARY})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mac/)
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux/)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

###############win source and headers###################
set(GLUONINPUT_LIB_SRCS_WIN )

set(GLUONINPUT_LIB_HEADERS_WIN )
###############win source and headers###################

###############mac source and headers###################
set(GLUONINPUT_LIB_SRCS_MAC	
	mac/macthread.cpp
	mac/code.cpp
    mac/detectmac.cpp
)

set(GLUONINPUT_LIB_HEADERS_MAC	
	mac/code.h
    mac/detectmac.h
	mac/macthread.h
    mac/inputdefinitions.h
	
)
###############mac source and headers###################

###############linux source and headers###################
set(GLUONINPUT_LIB_SRCS_LINUX	
	linux/linuxthread.cpp
	linux/code.cpp
    linux/detectlinux.cpp
)

set(GLUONINPUT_LIB_HEADERS_LINUX	
	linux/linuxthread.h
	linux/code.h
    linux/detectlinux.h
    linux/inputdefinitions.h
)
###############linux source and headers###################

###############common source and headers###################
set(GLUONINPUT_LIB_SRCS_COMMON
	 inputevent.cpp
    inputdevice.cpp
    mouse.cpp
    tablet.cpp
    keyboard.cpp
    joystick.cpp
    custominput.cpp
	threadabstract.cpp
    detect.cpp
    detectabstract.cpp

    #widgets/kclpressbutton.cpp
    #widgets/kclinputwidget.cpp
    #widgets/kclcustominputdialog.cpp
    #widgets/kclinfowidget.cpp
    #widgets/kcldevicemodel.cpp
)

set(GLUONINPUT_LIB_HEADERS_COMMON
    gluon_input_export.h
    detect.h
 gluoninput.h
    inputevent.h
    inputdevice.h
    mouse.h
    tablet.h
    keyboard.h
    joystick.h
    custominput.h
	detectabstract.h
)
###############common source and headers###################

qt4_automoc(${GLUONINPUT_LIB_SRCS_COMMON})

IF(WIN32)
    qt4_automoc(${GLUONINPUT_LIB_SRCS_WIN})
    add_library(GluonInput SHARED ${GLUONINPUT_LIB_SRCS_WIN} ${GLUONINPUT_LIB_SRCS_COMMON})
ELSEIF(APPLE)
    qt4_automoc(${kcl_LIB_SRCS_MAC})
    add_library(GluonInput SHARED ${GLUONINPUT_LIB_SRCS_MAC} ${GLUONINPUT_LIB_SRCS_COMMON})
ELSE()
    qt4_automoc(${GLUONINPUT_LIB_SRCS_LINUX})
    add_library(GluonInput SHARED ${GLUONINPUT_LIB_SRCS_LINUX} ${GLUONINPUT_LIB_SRCS_COMMON})
ENDIF()

set_target_properties(GluonInput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

target_link_libraries(GluonInput ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

#TODO: Fix the library path stuff so that we install it into the correct directory
if(APPLE)
    target_link_libraries(GluonInput ${IOKIT_LIBRARY}  ${COREFOUNDATION_LIBRARY})
    install(TARGETS GluonInput DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
elseif(WIN32)
else()
    install(TARGETS GluonInput DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

if(APPLE)
    install(
        FILES
        ${GLUONINPUT_LIB_HEADERS_MAC}
        ${GLUONINPUT_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
elseif(WIN32)
    install(
        FILES
        ${GLUONINPUT_LIB_HEADERS_WIN}
        ${GLUONINPUT_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
else()
    install(
        FILES
        ${GLUONINPUT_LIB_HEADERS_LINUX}
        ${GLUONINPUT_LIB_HEADERS_COMMON}
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input
        COMPONENT Devel
    )
endif()

#install(
#    FILES
#    detectabstract.h
#    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/input/
#    COMPONENT Devel
#)

#install(FILES
#widgets/kclpressbutton.h
#widgets/kclinputwidget.h
#widgets/kclcustominputdialog.h
#widgets/kclinfowidget.h
#widgets/kcldevicemodel.h
#DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl/widgets COMPONENT Devel)

