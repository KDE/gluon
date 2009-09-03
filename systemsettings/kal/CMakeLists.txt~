########### KCM ###############

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../../)
set(kcm_kal_PART_SRCS 
  kcmkal.cpp
)


kde4_add_plugin(kcm_kal ${kcm_kal_PART_SRCS})


target_link_libraries(kcm_kal ${KDE4_KIO_LIBS} kal)

install(TARGETS kcm_kal  DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kal.desktop DESTINATION  ${SERVICES_INSTALL_DIR} )



