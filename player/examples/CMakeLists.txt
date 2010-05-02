file(GLOB invaders
    "invaders/*"
)

file(GLOB pong
    "pong/*"
)

install(FILES ${invaders} DESTINATION ${DATA_INSTALL_DIR}/gluon/invaders)
install(FILES ${pong} DESTINATION ${DATA_INSTALL_DIR}/gluon/pong)