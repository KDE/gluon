gluon_unit_tests(
    MODULE GluonCore
    LIBRARIES ${GLUONCORE_LIBRARIES}
    TESTS gluonobjecttest metainfotest gdlserializertest singletontest
)
