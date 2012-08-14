#add_subdirectory(projectinspector)
add_subdirectory(distributionwizard)

if(BUILD_GLUON_CREATOR_VCS)
    add_subdirectory(vcs)
endif(BUILD_GLUON_CREATOR_VCS)

