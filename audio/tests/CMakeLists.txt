cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${GLUON_AUDIO_INCLUDES})

MACRO(GLUONAUDIO_UNIT_TESTS modulename)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable(${modulename}-${testname} ${testname}.cpp)
        target_link_libraries(${modulename}-${testname} ${GLUON_AUDIO_LIBS} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUONAUDIO_UNIT_TESTS)
MACRO(GLUONAUDIO_EXECUTABLE_TESTS)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${GLUON_AUDIO_LIBS} ${QT_QTTEST_LIBRARY})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUONAUDIO_EXECUTABLE_TESTS)

########### next target ###############

GLUONAUDIO_UNIT_TESTS(
    gluonaudio #modulename argument
    soundtest
)
