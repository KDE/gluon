## install the cmake files

file(GLOB cmakeFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.cmake")

set(module_install_dir ${DATA_INSTALL_DIR}/cmake/modules)

install( FILES 
	 FindKCL.cmake
	 FindKAL.cmake
	 FindKGL.cmake
	 FindGluon.cmake
	 FindGluonCommon.cmake
         DESTINATION ${module_install_dir})
