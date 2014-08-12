find_package(Qt5Widgets REQUIRED)

set(nodeeditor_SRCS
    qneblock.cpp
    qneconnection.cpp
    qneport.cpp
    qnodeseditor.cpp
)

set(nodeeditor_HEADERS
    qneblock.h
    qneconnection.h
    qneport.h
    qnodeseditor.h
)

gluon_add_library(Gluon::NodeEditor SHARED
    SOURCES ${nodeeditor_SRCS}
    HEADERS ${nodeeditor_HEADERS}
    LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets
)

set(qnodeeditor_SRCS
    main.cpp
    qnemainwindow.cpp
)

gluon_add_executable(qnodeeditor
    SOURCES ${qnodeeditor_SRCS}
    LIBRARIES Gluon::NodeEditor
)
