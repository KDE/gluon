PROJECT(gdlexample)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(gdlexample_SRCS
    propertywidgetitem.cpp
    propertywidget.cpp
    main.cpp
    mainwindow.cpp
    gameobjecttreemodel.cpp
    qobjecttreemodel.cpp
)

kde4_add_executable(gdlexample ${gdlexample_SRCS})
target_link_libraries(gdlexample ${GLUON_LIBRARY})
