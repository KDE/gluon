include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CREATOR_INCLUDE_DIRS}
)

########### next target ###############


gluon_unit_tests(
    MODULE GluonCreator
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    TESTS
)
