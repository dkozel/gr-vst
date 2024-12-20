find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_VST gnuradio-VST)

FIND_PATH(
    GR_VST_INCLUDE_DIRS
    NAMES gnuradio/VST/api.h
    HINTS $ENV{VST_DIR}/include
        ${PC_VST_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_VST_LIBRARIES
    NAMES gnuradio-VST
    HINTS $ENV{VST_DIR}/lib
        ${PC_VST_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-VSTTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_VST DEFAULT_MSG GR_VST_LIBRARIES GR_VST_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_VST_LIBRARIES GR_VST_INCLUDE_DIRS)
