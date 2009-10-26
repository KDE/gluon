if(WIN32)

include_directories(./win/)

elseif(APPLE)

include_directories(./mac/)

else()

include_directories(./linux/)

endif()

include_directories(./common ./)

###############win source and headers###################
set(kcl_LIB_SRCS_WIN )

set(kcl_LIB_HEADERS_WIN )
###############win source and headers###################

###############mac source and headers###################
set(kcl_LIB_SRCS_MAC

./mac/kclinputevent.cpp
./mac/kclthread.cpp
./mac/kclinput.cpp
./mac/kclmouse.cpp
./mac/kcltablet.cpp
./mac/kclkeyboard.cpp
./mac/kcljoystick.cpp
./mac/kclcode.cpp
./mac/kcldetectmac.cpp
./mac/kclcustominput.cpp

)

set(kcl_LIB_HEADERS_MAC 

./mac/kcl.h
./mac/kcl_export.h
./mac/kclinputevent.h
./mac/kclthread.h
./mac/kclinput.h
./mac/kclmouse.h
./mac/kcltablet.h
./mac/kclkeyboard.h
./mac/kcljoystick.h
./mac/kclcode.h
./mac/kcldetectmac.h
./mac/kclcustominput.h

)
###############mac source and headers###################

###############linux source and headers###################
set(kcl_LIB_SRCS_LINUX

./linux/kclinputevent.cpp
./linux/kclthread.cpp
./linux/kclinput.cpp
./linux/kclmouse.cpp
./linux/kcltablet.cpp
./linux/kclkeyboard.cpp
./linux/kcljoystick.cpp
./linux/kclcode.cpp
./linux/kcldetectlinux.cpp
./linux/kclcustominput.cpp

)

set(kcl_LIB_HEADERS_LINUX

./linux/kcl.h
./linux/kcl_export.h
./linux/kclinputevent.h
./linux/kclthread.h
./linux/kclinput.h
./linux/kclmouse.h
./linux/kcltablet.h
./linux/kclkeyboard.h
./linux/kcljoystick.h
./linux/kclcode.h
./linux/kcldetectlinux.h
./linux/kclcustominput.h

)
###############linux source and headers###################

###############common source and headers###################
set(kcl_LIB_SRCS_COMMON

kcldetect.cpp
./common/kcldetectabstract.cpp

widgets/kclpressbutton.cpp
widgets/kclinputwidget.cpp
widgets/kclcustominputdialog.cpp
widgets/kclinfowidget.cpp
widgets/kcldevicemodel.cpp
)

set(kcl_LIB_HEADERS_COMMON

kcldetect.h
./common/kcldetectabstract.h

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

set_target_properties(kcl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

target_link_libraries(kcl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

if(APPLE)
target_link_libraries(kcl ${IOKIT_LIBRARY}  ${COREFOUNDATION_LIBRARY})
endif()


if(APPLE)

install(TARGETS kcl DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

elseif(WIN32)
else()

install(TARGETS kcl ${INSTALL_TARGETS_DEFAULT_ARGS})

endif()

if(APPLE)

install(FILES

${kcl_LIB_HEADERS_MAC}
${kcl_LIB_HEADERS_COMMON}

DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)

elseif(WIN32)

install(FILES

${kcl_LIB_HEADERS_WIN}
${kcl_LIB_HEADERS_COMMON}

DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)

else()

install(FILES

${kcl_LIB_HEADERS_LINUX}
${kcl_LIB_HEADERS_COMMON}

DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)

endif()

install(FILES
widgets/kclpressbutton.h
widgets/kclinputwidget.h
widgets/kclcustominputdialog.h
widgets/kclinfowidget.h
widgets/kcldevicemodel.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl/widgets COMPONENT Devel)

