project(main)

find_package(KDE4 REQUIRED)
find_package(Qt4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen2 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Alut REQUIRED)
include(KDE4Defaults)

include_directories(${KDE4_INCLUDES})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories(${X11_Xrandr_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${EIGEN2_INCLUDE_DIR})

include_directories(${OPENAL_INCLUDE_DIR})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})




########### next target ###############

set(main_SRCS 
   main.cpp 

	)

kde4_add_executable(main ${main_SRCS} )

target_link_libraries(main gluon)

########### install files ###############

# install(TARGETS kglintro  ${INSTALL_TARGETS_DEFAULT_ARGS} )
