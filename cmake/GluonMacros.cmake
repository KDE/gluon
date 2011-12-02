# This file contains macros that are used inside the Gluon Project

macro(GLUON_UNIT_TESTS libraries modulename)
    foreach(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
    endforeach(testname)
endmacro(GLUON_UNIT_TESTS)

macro(GLUON_EXECUTABLE_TESTS libraries modulename1)
    foreach(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${libraries} ${QT_QTTEST_LIBRARY})
    endforeach(testname)
endmacro(GLUON_EXECUTABLE_TESTS)

macro(gluon_add_library _target _type)
    qt4_automoc(${ARGN})
    add_library(${_target} ${ARGN})
    string(TOUPPER ${_target} _target_uc)
    set_target_properties(${_target} PROPERTIES
        VERSION ${GLUON_VERSION_STRING}
        SOVERSION ${GLUON_VERSION_STRING}
        DEFINE_SYMBOL MAKE_${_target_uc}_LIB
        LINK_INTERFACE_LIBRARIES ""
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endmacro(gluon_add_library)

macro(gluon_target_link_libraries _target)
    target_link_libraries(${_target} ${ARGN})
    string(TOUPPER ${_target} _target_uc)
    set(${_target_uc}_LIBRARIES
        ${_target}
        ${ARGN}
        CACHE INTERNAL "Libraries required for ${_target}"
    )
endmacro(gluon_target_link_libraries)

macro(gluon_add_plugin _target)
    qt4_automoc(${ARGN})
    add_library(${_target} MODULE ${ARGN})
    string(TOUPPER ${_target} _target_uc)
    set_target_properties(${_target} PROPERTIES
        PREFIX ""
        DEFINE_SYMBOL MAKE_${_target_uc}_LIB
        INSTALL_RPATH_USE_LINK_PATH TRUE
        VERSION ${GLUON_VERSION_STRING}
        SOVERSION ${GLUON_VERSION_STRING}
    )
endmacro(gluon_add_plugin)

macro(gluon_add_executable _target)
    qt4_automoc(${ARGN})
    add_executable(${_target} ${ARGV})
endmacro(gluon_add_executable)

macro(gluon_include_directories _target)
    include_directories(${CMAKE_CURRENT_BINARY_DIR} ${ARGN})
    string(TOUPPER ${_target} _target_uc)
    set(${target_uc}_INCLUDES
        ${ARGN}
        CACHE INTERNAL "Includes required for ${_target}"
    )
endmacro(gluon_include_directories)

macro(gluon_setup_framework _target)
    if(APPLE)
        #hack for being able to set headers as public in a osx framework
        set(_public_headers ${ARGN})
        list(APPEND _public_headers ${_public_headers})

        set_target_properties(${_target} PROPERTIES FRAMEWORK TRUE)
        set_target_properties(${_target} PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
        set_target_properties(${_target} PROPERTIES PUBLIC_HEADER "${_public_headers}")

        set(MACOSX_FRAMEWORK_IDENTIFIER ${_target})
        set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
        set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
    endif(APPLE)
endmacro(gluon_setup_framework)
