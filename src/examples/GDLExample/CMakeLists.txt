PROJECT(gdlexample)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES} ${GLUON_INCLUDE_DIR}/gluon)

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(gdlexample_SRCS
    main.cpp
    mainwindow.cpp
)

kde4_add_executable(gdlexample ${gdlexample_SRCS})
target_link_libraries(gdlexample ${GLUON_LIBRARY})
