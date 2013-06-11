project (gluonplayerdesktop)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})
 
set(gluonplayerdesktop_SRCS 
  main.cpp
  mainwindow.cpp
)
 
kde4_add_executable(gluonplayerdesktop ${gluonplayerdesktop_SRCS})
target_link_libraries(gluonplayerdesktop ${KDE4_KDEUI_LIBS})
