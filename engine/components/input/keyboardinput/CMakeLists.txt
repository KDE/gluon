project(ddd)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES} ${GLUON_INCLUDE_DIR}/gluon)

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ddd_SRCS 
    kclinputcomponent.cpp
   )

#QT4_ADD_RESOURCES(gluon_RCC_SRCS ${gluon_RCCS})
kde4_add_library(ddd ${ddd_SRCS})
set_target_properties(ddd PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)
target_link_libraries(ddd ${GLUON_LIBRARY})