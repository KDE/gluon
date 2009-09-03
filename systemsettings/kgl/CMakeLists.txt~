########### KCM ###############

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../../)
set(kcm_kgl_PART_SRCS 
  kcmkgl.cpp
)


kde4_add_plugin(kcm_kgl ${kcm_kgl_PART_SRCS})


target_link_libraries(kcm_kgl ${KDE4_KIO_LIBS} kgl)

install(TARGETS kcm_kgl  DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kgl.desktop DESTINATION  ${SERVICES_INSTALL_DIR} )



