include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CREATOR_INCLUDE_DIRS}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_CREATOR_LIBS}"   # libraries arguement
    "gluoncreator"            # modulename argument

    # Source files without the extension
)
