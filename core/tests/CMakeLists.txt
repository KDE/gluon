include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDE_DIRS}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_CORE_LIBS}"    # libraries arguement
    "gluoncore"             # modulename argument

    # Source files without the extension
    #gdlhandlertest
    gluonobjecttest
    metainfotest
)
