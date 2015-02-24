# Try to find Asset Importer (AssImp) libraries
# Once done this will define
#
#  ASSIMP_FOUND       - System has AssImp
#  ASSIMP_INCLUDE_DIRS - Include directories for AssImp
#  ASSIMP_LIBRARIES     - The AssImp Libraries
#

find_path(ASSIMP_INCLUDE_DIRS
    version.h
    PATH_SUFFIXES
    assimp
)

find_library(ASSIMP_LIBRARIES
    NAMES assimp
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AssImp DEFAULT_MSG ASSIMP_INCLUDE_DIRS ASSIMP_LIBRARIES)

mark_as_advanced(ASSIMP_INCLUDE_DIRS ASSIMP_LIBRARIES)
