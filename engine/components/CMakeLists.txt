#Use this to add new components to the build
#add_subdirectory($TYPE/somecomponent)

if(BUILD_AUDIO_COMPONENTS)
    add_subdirectory(audio/soundemitter)
    add_subdirectory(audio/soundlistener)
endif()

if(BUILD_GRAPHICS_COMPONENTS)
    #TODO: Port to new rendering engine
    #add_subdirectory(graphics/animatedspriterenderer)
    add_subdirectory(graphics/cameracontroller)
    add_subdirectory(graphics/spriterenderer)
    #add_subdirectory(graphics/interfacerenderer)
    if(GLUON_GRAPHICS_HAS_MESH)
        #TODO: Port to new rendering engine
        #add_subdirectory(graphics/meshrenderer)
    endif(GLUON_GRAPHICS_HAS_MESH)
endif()
if(BUILD_PHYSICS_COMPONENTS)
    #add_subdirectory(physics)
endif()
if(BUILD_OTHER_COMPONENTS)
    if (BUILD_GLUON_SMARTS)
        add_subdirectory(other/btcomponents)
    endif()
#     add_subdirectory(scripting)
endif()
