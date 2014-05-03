# This file contains macros that are used inside the Gluon Project

MACRO(GLUON_UNIT_TESTS libraries modulename)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUON_UNIT_TESTS)

MACRO(GLUON_EXECUTABLE_TESTS libraries modulename1)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUON_EXECUTABLE_TESTS)

macro(gluon_add_library _target _type)
    set( _sources "" )
    set( _headers "" )
    set( _libs "" )

    set( _current_target "_sources" )

    foreach( _arg ${ARGN} )
        string( TOLOWER ${_arg} _arg_lc )
        if( ${_arg_lc} STREQUAL "sources" )
            set( _current_target "_sources" )
        elseif( ${_arg_lc} STREQUAL "headers" )
            set( _current_target "_headers" )
        elseif( ${_arg_lc} STREQUAL "libraries" )
            set( _current_target "_libs" )
        else()
            list( APPEND ${_current_target} ${_arg} )
        endif()
    endforeach()

    add_library( ${_target} ${_type} ${_sources} ${_headers} )
    if( CMAKE_VERSION VERSION_LESS "2.8.6" )
        automoc4( ${_target} ${_sources} )
    endif()

    string( TOUPPER ${_target} _target_uc )
    set_target_properties( ${_target} PROPERTIES
        VERSION ${GLUON_VERSION_STRING}
        SOVERSION ${GLUON_VERSION_STRING}
        DEFINE_SYMBOL MAKE_${_target_uc}_LIB
    )

    target_link_libraries( ${_target} ${_libs} )
    set(${_target_uc}_LIBRARIES
        ${_target}
        ${_libs}
        CACHE INTERNAL "Libraries required for ${_target}"
    )

    if( APPLE )
        _gluon_setup_framework( ${_target} ${_headers} )
    endif()

    install( TARGETS ${_target}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT ${_target}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
        FRAMEWORK DESTINATION ${LIB_INSTALL_DIR} COMPONENT ${_target}
    )

    string( REGEX REPLACE "[A-Z][a-z]+([A-Z][a-z]+).*" "\\1" _target_include_dir ${_target} )
    string( TOLOWER ${_target_include_dir} _target_include_dir )

    install( FILES ${_headers} 
        DESTINATION ${INCLUDE_INSTALL_DIR}/${_target_include_dir} COMPONENT ${_target}
    )
endmacro(gluon_add_library)

macro(gluon_add_plugin _target _component)
    set( _sources "" )
    set( _libs "" )
    set( _dest "" )

    set( _current_target "_sources" )

    foreach( _arg ${ARGN} )
        string( TOLOWER ${_arg} _arg_lc )
        if( ${_arg_lc} STREQUAL "sources" )
            set( _current_target "_sources" )
        elseif( ${_arg_lc} STREQUAL "libraries" )
            set( _current_target "_libs" )
        elseif( ${_arg_lc} STREQUAL "destination" )
            set( _current_target "_dest" )
        else()
            list( APPEND ${_current_target} ${_arg} )
        endif()
    endforeach()

    if( "${_dest}" STREQUAL "" )
        set( _dest ${PLUGIN_INSTALL_DIR} )
    endif()

    string( TOUPPER "${_component}_libraries" _comp_uc )
    list( APPEND _libs ${${_comp_uc}} )

    add_library( ${_target} MODULE ${_sources} )
    if( CMAKE_VERSION VERSION_LESS "2.8.6" )
        automoc4( ${_target} ${_sources} )
    endif()

    string( TOUPPER ${_target} _target_uc )
    set_target_properties(${_target} PROPERTIES
        PREFIX ""
    )
    
    target_link_libraries( ${_target} ${_libs} )

    install( TARGETS ${_target}
        DESTINATION ${_dest} COMPONENT ${_component}
    )
endmacro(gluon_add_plugin)

macro(gluon_add_executable _target)
    set( _sources "" )
    set( _headers "" )
    set( _libs "" )

    set( _current_target "_sources" )

    foreach( _arg ${ARGN} )
        string( TOLOWER ${_arg} _arg_lc )
        if( ${_arg_lc} STREQUAL "sources" )
            set( _current_target "_sources" )
        elseif( ${_arg_lc} STREQUAL "headers" )
            set( _current_target "_headers" )
        elseif( ${_arg_lc} STREQUAL "libraries" )
            set( _current_target "_libs" )
        else()
            list( APPEND ${_current_target} ${_arg} )
        endif()
    endforeach()

    add_executable( ${_target} ${_sources} )
    if( CMAKE_VERSION VERSION_LESS "2.8.6" )
        automoc4( ${_target} ${_sources} )
    endif()

    target_link_libraries( ${_target} ${_libs} )

    install(TARGETS ${_target} DESTINATION ${BIN_INSTALL_DIR} COMPONENT ${_target})
endmacro(gluon_add_executable)

macro(gluon_include_directories _target)
    include_directories(${ARGN})
    string(TOUPPER ${_target} _target_uc)
    set(${_target_uc}_INCLUDE_DIRS
        ${ARGN}
        CACHE INTERNAL "Includes required for ${_target}"
    )
endmacro(gluon_include_directories)

macro( _gluon_setup_framework _target )

    #hack for being able to set headers as public in a osx framework
    set(_public_headers ${ARGN})
    list(APPEND _public_headers ${_public_headers})

    set_target_properties(${_target} PROPERTIES FRAMEWORK TRUE)
    set_target_properties(${_target} PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(${_target} PROPERTIES PUBLIC_HEADER "${_public_headers}")

    set(MACOSX_FRAMEWORK_IDENTIFIER ${_target})
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endmacro( _gluon_setup_framework )

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
