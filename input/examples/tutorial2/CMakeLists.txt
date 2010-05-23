project(tutorial2)
cmake_minimum_required(VERSION 2.6)

if(APPLE)
	find_package(Qt4 4.6 REQUIRED)
	find_library(GluonInput NAMES GluonInput)
	message("-- Found GluonInput:" ${GluonInput})
	
	find_library(GluonCore NAMES GluonCore)
	message("-- Found GluonCore:" ${GluonCore})
	
	set(GLUON_INPUT_LIBS ${GluonCore} ${GluonInput})
	set(GLUON_INPUT_INCLUDES ${GluonInput}/Headers ${GluonCore}/Headers)

else()
	find_package(GluonInput REQUIRED)
endif()

include_directories(${GLUON_INPUT_INCLUDES})
include_directories(${CMAKE_BINARY_DIR})

########### next target ###############

set(tutorial2_SRCS
    gameloop.cpp
    main.cpp
)

qt4_automoc(${tutorial2_SRCS})
add_executable(tutorial2 ${tutorial2_SRCS})
target_link_libraries(tutorial2 ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
