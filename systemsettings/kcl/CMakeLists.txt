
########### KCM ###############

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    include_directories(../../kcl/win/)
elseif(APPLE)
    include_directories(../../kcl/mac/)
else()
    include_directories(../../kcl/linux/)
endif()
include_directories(../../ ../../kcl/)

set(kcm_kcl_PART_SRCS 
  kcmkcl.cpp
)


kde4_add_plugin(kcm_kcl ${kcm_kcl_PART_SRCS})


target_link_libraries(kcm_kcl ${KDE4_KIO_LIBS} kcl)

install(TARGETS kcm_kcl  DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kcl.desktop DESTINATION  ${SERVICES_INSTALL_DIR} )

