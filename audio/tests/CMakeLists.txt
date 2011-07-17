cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${GLUON_AUDIO_INCLUDES})

add_definitions(${QT_DEFINITIONS})

MACRO(GLUONAUDIO_UNIT_TESTS)
       FOREACH(testname ${ARGN})
               qt4_automoc(${testname}.cpp)
               add_executable(gluonaudio-${testname} ${testname}.cpp)
               target_link_libraries(gluonaudio-${testname} ${GLUON_AUDIO_LIBS} ${QT_QTTEST_LIBRARY})
               add_test("gluonaudio-${testname}" gluonaudio-${testname})
               if(WINCE)
                target_link_libraries("gluonaudio-${testname}" ${WCECOMPAT_LIBRARIES})
               endif(WINCE)
       ENDFOREACH(testname)
ENDMACRO(GLUONAUDIO_UNIT_TESTS)
MACRO(GLUONAUDIO_EXECUTABLE_TESTS)
       FOREACH(testname ${ARGN})
               qt4_automoc(${testname}.cpp)
               add_executable("gluonaudIo-${testname}" ${testname}.cpp)
               target_link_libraries("gluonaudio-${testname}" ${GLUON_AUDIO_LIBS} ${QT_QTTEST_LIBRARY})
               if(WINCE)
                target_link_libraries("gluonaudio-${testname}" ${WCECOMPAT_LIBRARIES})
               endif(WINCE)
       ENDFOREACH(testname)
ENDMACRO(GLUONAUDIO_EXECUTABLE_TESTS)

enable_testing()

########### next target ###############

GLUONAUDIO_UNIT_TESTS(
    soundtest
)
