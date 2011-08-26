
set(gluonexamples_core_gdlparser_SRCS
    debugvisitor.cpp
    main.cpp
)

add_executable(gluonexamples_core_gdlparser ${gluonexamples_core_gdlparser_SRCS})

target_link_libraries(gluonexamples_core_gdlparser ${GLUON_CORE_LIBS})