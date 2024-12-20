# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT VST_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT VST_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND VST_python_files
    VSTSrc_python.cc
    VSTSrcI16_python.cc python_bindings.cc)

gr_pybind_make_oot(VST ../../.. gr::VST "${VST_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET VST_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:VST_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/VST/)

install(
    TARGETS VST_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/VST
    COMPONENT pythonapi)
