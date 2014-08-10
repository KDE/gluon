# This file contains macros that are used inside the Gluon Project
include( CMakeParseArguments )

macro( gluon_unit_tests )
    cmake_parse_arguments("" "" "MODULE" "LIBRARIES;TESTS" ${ARGN})
    if( _UNPARSED_ARGUMENTS )
        message(FATAL_ERROR "Unknown keywords given to gluon_unit_tests: ${_UNPARSED_ARGUMENTS}")
    endif()

    string( REGEX REPLACE "([^a-zA-Z])" "" _module_simple ${_MODULE} )

    foreach(_test ${_TESTS})
	set(_test_target "${_module_simple}-${_test}")
        add_executable(${_test_target} "${_test}.cpp")
        target_link_libraries(${_test_target} ${_MODULE} ${_LIBRARIES} Qt5::Test)
        add_test(${_test_target} ${_module_simple}-${_test})
    endforeach()
endmacro(gluon_unit_tests)

macro( gluon_add_library _target _type )
    cmake_parse_arguments("" "" "" "SOURCES;HEADERS;LIBRARIES;INCLUDES" ${ARGN})
    if( _UNPARSED_ARGUMENTS )
        message(FATAL_ERROR "Unknown keywords given to gluon_add_library: ${_UNPARSED_ARGUMENTS}")
    endif()

    string( REGEX REPLACE "([^a-zA-Z])" "" _target_simple ${_target} )

    add_library( ${_target_simple} ${_type} ${_SOURCES} ${_HEADERS} )
    if( NOT ${_target_simple} STREQUAL ${_target} )
        add_library( ${_target} ALIAS ${_target_simple} )
    endif()

    string( REGEX REPLACE "[A-Z][a-z]+([A-Z][a-z]+).*" "\\1" _target_short ${_target_simple} )
    string( TOUPPER ${_target_simple} _target_uc )
    string( TOLOWER ${_target_short} _target_include_dir )

    set_target_properties( ${_target_simple} PROPERTIES
        VERSION ${GLUON_VERSION_STRING}
        SOVERSION ${GLUON_VERSION_STRING}
        DEFINE_SYMBOL MAKE_${_target_uc}_LIB
        EXPORT_NAME ${_target_short}
    )

    target_include_directories( ${_target_simple} PUBLIC ${_INCLUDES} )
    target_include_directories( ${_target_simple} PUBLIC "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/${_target_include_dir}>" )
    target_link_libraries( ${_target_simple} PUBLIC ${_LIBRARIES} )

    install( TARGETS ${_target_simple}
        EXPORT ${_target_simple}Targets
        RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT ${_target}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
        FRAMEWORK DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
    )

    install( FILES ${_headers} 
        DESTINATION ${INCLUDE_INSTALL_DIR}/${_target_include_dir}
        COMPONENT ${_target}
    )

    install( EXPORT ${_target_simple}Targets
        DESTINATION ${LIB_INSTALL_DIR}/cmake/${_target_simple}
        NAMESPACE Gluon::
        COMPONENT ${_target}
    )
endmacro(gluon_add_library)

macro(gluon_add_plugin _target)
    cmake_parse_arguments("" "" "DESTINATION;MODULE" "SOURCES;LIBRARIES" ${ARGN})
    if( _UNPARSED_ARGUMENTS )
        message(FATAL_ERROR "Unknown keywords given to gluon_add_plugin: ${_UNPARSED_ARGUMENTS}")
    endif()

    if( "${_DESTINATION}" STREQUAL "" )
        set( _DESTINATION ${PLUGIN_INSTALL_DIR} )
    endif()

    add_library( ${_target} MODULE ${_SOURCES} )

    string( TOUPPER ${_target} _target_uc )
    set_target_properties(${_target} PROPERTIES PREFIX "" )
    
    target_link_libraries( ${_target} ${_MODULE} ${_LIBRARIES} )

    install( TARGETS ${_target} DESTINATION ${_DESTINATION} COMPONENT ${_MODULE}    )
endmacro(gluon_add_plugin)

macro(gluon_add_executable _target)
    cmake_parse_arguments("" "" "" "SOURCES;HEADERS;LIBRARIES" ${ARGN})
    if( _UNPARSED_ARGUMENTS )
        message(FATAL_ERROR "Unknown keywords given to gluon_add_executable: ${_UNPARSED_ARGUMENTS}")
    endif()

    add_executable( ${_target} ${_SOURCES} )

    target_link_libraries( ${_target} ${_LIBRARIES} )

    install(TARGETS ${_target} DESTINATION ${BIN_INSTALL_DIR} COMPONENT ${_target})
endmacro(gluon_add_executable)

# macro( _gluon_setup_framework _target )
#
#     #hack for being able to set headers as public in a osx framework
#     set(_public_headers ${ARGN})
#     list(APPEND _public_headers ${_public_headers})
#
#     set_target_properties(${_target} PROPERTIES FRAMEWORK TRUE)
#     set_target_properties(${_target} PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
#     set_target_properties(${_target} PROPERTIES PUBLIC_HEADER "${_public_headers}")
#
#     set(MACOSX_FRAMEWORK_IDENTIFIER ${_target})
#     set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
#     set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
# endmacro( _gluon_setup_framework )

macro( log_status _target )
    string( TOUPPER ${_target} _target_uc )
    message( STATUS "Build ${_target} (BUILD_${_target_uc}): ${BUILD_${_target_uc}}" )
    if( BUILD_${_target_uc} AND DEFINED ${_target_uc}_STATUS )
        foreach( _message ${${_target_uc}_STATUS} )
            message( STATUS "└> ${_message}" )
        endforeach()
    endif()
endmacro( log_status )

macro( save_status _target )
    string( TOUPPER ${_target} _target_uc )
    set( ${_target_uc}_STATUS ${ARGN} CACHE INTERNAL "Status of module ${_target}" )
endmacro( save_status )

macro( gluon_add_subdirectories )
    foreach( _arg ${ARGN} )
        string( TOUPPER ${_arg} _arg_uc )
        if( BUILD_${_arg_uc} )
            add_subdirectory( ${_arg} )
        endif()
    endforeach()
endmacro( gluon_add_subdirectories )
