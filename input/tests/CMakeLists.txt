cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${GLUON_INPUT_INCLUDES})

MACRO(GLUONINPUT_UNIT_TESTS modulename)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable(${modulename}-${testname} ${testname}.cpp)
        target_link_libraries(${modulename}-${testname} ${GLUON_INPUT_LIBS} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUONINPUT_UNIT_TESTS)
MACRO(GLUONINPUT_EXECUTABLE_TESTS modulename)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${GLUON_INPUT_LIBS} ${QT_QTTEST_LIBRARY})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUONINPUT_EXECUTABLE_TESTS)

enable_testing()

########### next target ###############

GLUONINPUT_UNIT_TESTS(
    gluoninput # modulename argument
    inputbuffertest
)
