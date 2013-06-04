include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_GRAPHICS_INCLUDE_DIRS}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_GRAPHICS_LIBS}"    # libraries arguement
    "gluongraphics"             # modulename argument

    # Source files without the extension
)
