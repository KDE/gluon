# - Try to find Gluon
#
# Once done this will define
#  GLUON_FOUND - system has Gluon
#  GLUON_INCLUDES - all include directories required for Gluon, use it with KDE4_INCLUDES
#  GLUON_INCLUDE_DIR - the Gluon include directory
#  GLUON_LIBRARY - the Gluon library
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_CREATOR_LIBRARY AND GLUON_CREATOR_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_CREATOR_FOUND TRUE)
endif (GLUON_CREATOR_LIBRARY AND GLUON_CREATOR_INCLUDE_DIR)
  
if (GluonCreator_FIND_REQUIRED)
  set(_gluonCreatorReq "REQUIRED")
endif (GluonCreator_FIND_REQUIRED)

find_package(KDE4 ${_gluonCreatorReq})
find_package(Gluon ${_gluonCreatorReq})

find_path(GLUON_CREATOR_INCLUDE_DIR
  NAMES
  gluoncreator/gluoncreator_macros.h
  PATHS
  ${INCLUDE_INSTALL_DIR}
)
        
set(GLUON_CREATOR_INCLUDES
    ${GLUON_CREATOR_INCLUDE_DIR}
    ${GLUON_INCLUDES}
    ${KDE4_INCLUDES}
)
        
find_library(GLUON_CREATOR_LIBRARY NAMES gluoncreator
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_CREATOR_LIBS
    ${KDE4_KDEUI_LIBS}
    ${GLUON_LIBRARY}
    ${GLUON_CREATOR_LIBRARY})
        
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonCreator DEFAULT_MSG GLUON_CREATOR_LIBRARY GLUON_CREATOR_INCLUDE_DIR)
        