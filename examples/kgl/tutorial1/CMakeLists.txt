project(main)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})



########### next target ###############

set(main_SRCS 
   main.cpp 

	)

kde4_add_executable(kgl_tutorial1 ${main_SRCS})
target_link_libraries(kgl_tutorial1 ${GLUON_LIBRARY})

########### install files ###############

# install(TARGETS kglintro  ${INSTALL_TARGETS_DEFAULT_ARGS} )
