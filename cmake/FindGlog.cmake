#.rst:
# FindGlog
# -----------
#
# Try to find the glog logging processing library
#
# Once done this will define
#
# ::
#
#   GLOG_FOUND - System has Glog
#   GLOG_INCLUDE_DIR - The Glog include directory
#   GLOG_LIBRARIES - The libraries needed to use Glog
#   GLOG_DEFINITIONS - Compiler switches required for using Glog
#   GLOG_VERSION_STRING - the version of Glog found (since CMake 2.8.8)

# use pkg-config to get the directories and then use these values
# in the find_path() and find_library() calls
find_package(PkgConfig QUIET)
PKG_CHECK_MODULES(PC_GLOG QUIET libglog)

find_path(GLOG_INCLUDE_DIR NAMES logging.h
   PATH_SUFFIXES glog
   HINTS
   ${PC_GLOG_INCLUDEDIR}
   ${PC_GLOG_INCLUDE_DIRS}
   )

find_library(GLOG_LIBRARIES NAMES glog
   HINTS
   ${PC_GLOG_LIBDIR}
   ${PC_GLOG_LIBRARY_DIRS}
   )

if(PC_GLOG_VERSION)
    set(GLOG_VERSION_STRING ${PC_GLOG_VERSION})
endif()

# handle the QUIETLY and REQUIRED arguments and set GLOG_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Glog
                                  REQUIRED_VARS GLOG_LIBRARIES GLOG_INCLUDE_DIR
                                  VERSION_VAR GLOG_VERSION_STRING)

mark_as_advanced(GLOG_INCLUDE_DIR GLOG_LIBRARIES)

if (GLOG_FOUND AND NOT TARGET Glog::Glog)
    add_library(Glog::Glog UNKNOWN IMPORTED)
    set_target_properties(Glog::Glog PROPERTIES
        IMPORTED_LOCATION "${GLOG_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIR}"
    )
endif()


