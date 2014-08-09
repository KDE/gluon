gluon_add_plugin( gluoninput_platform
    MODULE Gluon::Input
    SOURCES qtplatform.cpp
)

gluon_add_plugin( gluoninput_qt_keyboard
    MODULE Gluon::Input
    SOURCES qtkeyboardplugin.cpp qtkeyboarddevice.cpp
)

gluon_add_plugin( gluoninput_qt_mouse
    MODULE Gluon::Input
    SOURCES qtmouseplugin.cpp qtmousedevice.cpp
)