include_directories(${GLUONCORE_INCLUDE_DIRS} common)

add_subdirectory(common)
add_subdirectory(lib)

if(KDE4_FOUND)
    include_directories(${KDE4_INCLUDES})
    add_subdirectory(editor)
else(KDE4_FOUND)
    message(STATUS "KDE libraries are not found - not building the Smarts Editor")
endif(KDE4_FOUND)



