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

add_definitions(${QT_DEFINITIONS})

MACRO(GLUONCORE_UNIT_TESTS)
       FOREACH(testname ${ARGN})
               qt4_automoc(${testname}.cpp)
               add_executable(gluoncore-${testname} ${testname}.cpp)
               target_link_libraries(gluoncore-${testname} ${GLUON_CORE_LIBS} ${QT_QTTEST_LIBRARY})
               add_test("gluoncore-${testname}" gluoncore-${testname})
               if(WINCE)
                target_link_libraries(${testname} ${WCECOMPAT_LIBRARIES})
               endif(WINCE)
       ENDFOREACH(testname)
ENDMACRO(GLUONCORE_UNIT_TESTS)
MACRO(GLUONCORE_EXECUTABLE_TESTS)
       FOREACH(testname ${ARGN})
               qt4_automoc(${testname}.cpp)
               add_executable(${testname} ${testname}.cpp)
               target_link_libraries(${testname} ${GLUON_CORE_LIBS} ${QT_QTTEST_LIBRARY})
               if(WINCE)
                target_link_libraries(${testname} ${WCECOMPAT_LIBRARIES})
               endif(WINCE)
       ENDFOREACH(testname)
ENDMACRO(GLUONCORE_EXECUTABLE_TESTS)

enable_testing()

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

GLUONCORE_UNIT_TESTS(
    gluonobjecttest
)
