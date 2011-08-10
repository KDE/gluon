# - Try to find GLEE
# Once done this will define
#  
#  GLEE_FOUND        - system has OpenGLES
#  GLEE_INCLUDE_DIR  - the GLES include directory
#  GLEE_LIBRARY	 - the GLES library
#  GLEE_LIBS         - Link this to use OpenGLES
#   

FIND_PATH(GLEE_INCLUDE_DIR GL/GLee.h)

FIND_LIBRARY(GLEE_LIBRARY
  NAMES GLee
        libglee
  PATHS /opt/graphics/OpenGL/lib
        /usr/openwin/lib
        /usr/shlib /usr/X11R6/lib
        /usr/lib
        ${LIB_INSTALL_DIR}
)

SET( GLEE_FOUND "NO" )
IF(GLEE_LIBRARY)
    SET( GLEE_LIBRARIES  ${GLEE_LIBRARY})
    SET( GLEE_FOUND "YES" )
ENDIF(GLEE_LIBRARY)
