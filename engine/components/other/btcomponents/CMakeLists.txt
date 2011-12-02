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

gluon_add_plugin(gluon_component_behaviortree ${behaviortreecomponent_SRCS})
target_link_libraries(gluon_component_behaviortree GluonEngine ${GLUONSMARTS_LIBS})

install(
    TARGETS
    gluon_component_behaviortree
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
