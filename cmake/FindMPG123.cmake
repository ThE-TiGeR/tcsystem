# - Try to find MPG123 Toolkit
# Once done this will define
#
#  MPG123_FOUND - system has MPG123
#  MPG123_INCLUDE_DIR1 - the MPG123 include directory
#  MPG123_INCLUDE_DIR2 - for the mpg123.h.in file because on windows it is not configured
#  MPG123_LIBRARIES - Link these to use MPG123

#=============================================================================
# Copyright 2006-2010 Thomas Goessler
#=============================================================================

if (UNIX)
    FIND_PATH(MPG123_INCLUDE_DIR1 mpg123.h)
    FIND_PATH(MPG123_INCLUDE_DIR2 mpg123.h)
else ()
    FIND_PATH(MPG123_INCLUDE_DIR1 mpg123.h)
    FIND_PATH(MPG123_INCLUDE_DIR2 mpg123.h.in)
endif ()

FIND_LIBRARY(MPG123_LIBRARIES NAMES libmpg123 mpg123 )

# handle the QUIETLY and REQUIRED arguments and set MPG123_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(mpg123 DEFAULT_MSG MPG123_LIBRARIES MPG123_INCLUDE_DIR1 MPG123_INCLUDE_DIR2)

MARK_AS_ADVANCED(MPG123_INCLUDE_DIR MPG123_INCLUDE_DIR2 MPG123_LIBRARIES)


