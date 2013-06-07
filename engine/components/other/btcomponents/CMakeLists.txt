include_directories(${GLUONSMARTS_INCLUDE_DIRS})

set(behaviortreecomponent_SRCS
    btAssetprivate.cpp
    btAsset.cpp
    treeprivate.cpp
    tree.cpp
    characterprivate.cpp
    character.cpp
    btcharacterscriptable.cpp
    btnodescriptable.cpp
    viewcone.cpp
    viewconeprivate.cpp
    perceptionatom.cpp
    perceptionatomprivate.cpp
    perceptioninfo.cpp
    perceptioninfoprivate.cpp
    btperceptioninfoscriptable.cpp
)

gluon_add_plugin(gluon_component_behaviortree GluonEngine
    SOURCES ${behaviortreecomponent_SRCS}
    LIBRARIES ${GLUONSMARTS_LIBRARIES}
)
