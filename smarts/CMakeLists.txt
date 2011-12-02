include_directories(${GLUONCORE_INCLUDES} common)

add_subdirectory(common)
add_subdirectory(lib)

find_package(KDE4)
if(KDE4_FOUND)
    include_directories(${KDE4_INCLUDES})
    if(BUILD_GLUON_SMARTS_EDITOR)
        add_subdirectory(editor)
    endif(BUILD_GLUON_SMARTS_EDITOR)
else(KDE4_FOUND)
    message(STATUS "KDE libraries are not found - not building the Smarts BtEditor")
endif(KDE4_FOUND)



