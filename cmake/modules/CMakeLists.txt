## install the cmake files

file(GLOB cmakeFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.cmake")

if(APPLE OR WIN32)
set(module_install_dir ${CMAKE_INSTALL_PREFIX}/share/apps/cmake/modules)
else()
set(module_install_dir ${DATA_INSTALL_DIR}/cmake/modules)
endif()

install( FILES 
	 FindKCL.cmake
	 FindKAL.cmake
	 FindKGL.cmake
	 FindGluon.cmake
	 FindGluonCommon.cmake
         DESTINATION ${module_install_dir})
