project(shader_demo)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

remove_definitions(-DNDEBUG)
add_definitions(-DDEBUG -DKDE_DEFAULT_DEBUG_AREA=989)

########### next target ###############

set(main_SRCS 
    main.cpp
    mainwindow.cpp
   )

kde4_add_executable(shader_demo ${main_SRCS})
target_link_libraries(shader_demo ${GLUON_LIBRARY})

########### install files ###############

#install(TARGETS kglintro  ${INSTALL_TARGETS_DEFAULT_ARGS} )
