project(phonalplayer)
cmake_minimum_required(VERSION 2.6)

find_package(Qt REQUIRED)
find_library(lib_phonon phonon)
find_package(OpenAL 1.8 REQUIRED)
find_library(lib_alut alut)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(phonalplayer_SRCS
    alsource.cpp
    main.cpp
    )

qt4_automoc(${phonalplayer_SRCS})

add_executable(phonalplayer ${phonalplayer_SRCS})

target_link_libraries(phonalplayer ${QT_QTCORE_LIB} ${lib_phonon} ${OPENAL_LIBRARY} ${lib_alut})
