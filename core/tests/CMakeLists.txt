cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCoreTest)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
)

MACRO(GLUON_UNIT_TESTS modulename)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${GLUON_TEST_LIBS} ${QT_QTTEST_LIBRARY})
        add_test("${modulename}-${testname}" ${modulename}-${testname})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUON_UNIT_TESTS)
MACRO(GLUON_EXECUTABLE_TESTS)
    FOREACH(testname ${ARGN})
        qt4_automoc(${testname}.cpp)
        add_executable("${modulename}-${testname}" ${testname}.cpp)
        target_link_libraries("${modulename}-${testname}" ${GLUON_TEST_LIBS} ${QT_QTTEST_LIBRARY})
        if(WINCE)
            target_link_libraries("${modulename}-${testname}" ${WCECOMPAT_LIBRARIES})
        endif(WINCE)
    ENDFOREACH(testname)
ENDMACRO(GLUON_EXECUTABLE_TESTS)

set(GluonCoreTest_SRCS
    main.cpp
    testgluoncore.cpp
)

set(GluonCoreTest_HDRS
    testgluoncore.h
)

qt4_automoc(${GluonCoreTest_SRCS})

add_executable(GluonCoreTest ${GluonCoreTest_SRCS})
target_link_libraries(GluonCoreTest GluonCore ${QT_QTTEST_LIBRARY} ${GLUON_CORE_LIBS})

########### next target ###############

#Set the library variable that is needed for the testing
set(GLUON_TEST_LIBS ${GLUON_CORE_LIBS})

GLUON_UNIT_TESTS(
    "gluoncore" # modulename argument
    gluonobjecttest
)
