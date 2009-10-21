PROJECT(gluoncreator)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(gluoncreator_SRCS
    propertywidgetitem.cpp
    propertywidget.cpp
    main.cpp
    mainwindow.cpp
    gameobjecttreemodel.cpp
    qobjecttreemodel.cpp
)

kde4_add_executable(gluoncreator ${gluoncreator_SRCS})
target_link_libraries(gluoncreator ${GLUON_LIBRARY})
