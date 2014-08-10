option( BUILD_GLUONSMARTS_EDITOR "Build SMARTS Game AI Editor" OFF )

include_directories(common)

add_subdirectory(common)
add_subdirectory(lib)
if(BUILD_GLUONSMARTS_EDITOR)
    add_subdirectory(editor)
endif(BUILD_GLUONSMARTS_EDITOR)

save_status( GluonSmarts
    "Build the SMARTS Game AI Editor (BUILD_GLUONSMARTS_EDITOR): ${BUILD_GLUONSMARTS_EDITOR}"
)
