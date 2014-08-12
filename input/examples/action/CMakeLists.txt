qt5_wrap_ui( actionwindow_ui actionwindow.ui )

gluon_add_executable(gluonexamples_input_action
    SOURCES main.cpp actionwindow.cpp ${actionwindow_ui}
    LIBRARIES Gluon::Input Qt5::Widgets
)
