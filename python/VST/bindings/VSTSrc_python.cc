/*
 * Copyright 2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(VSTSrc.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(ee30af13803610541a4cf5b1f635d5fb)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/VST/VSTSrc.h>
// pydoc.h is automatically generated in the build directory
#include <VSTSrc_pydoc.h>

void bind_VSTSrc(py::module& m)
{

    using VSTSrc    = gr::VST::VSTSrc;    

    py::class_<VSTSrc, gr::block, gr::basic_block,
        std::shared_ptr<VSTSrc>>(m, "VSTSrc")

        .def(py::init(&VSTSrc::make),
           py::arg("resname") =  "RIO0",
           py::arg("iqrate") = 1e6,
           py::arg("carrierFreq") = 1e9,
           py::arg("reflevel") = 0)
		.def("stop",
		   & VSTSrc::stop)
		.def("set_carrierFreq",
		   & VSTSrc::set_carrierFreq,
           py::arg("carrierFreq") = 1e9)
		.def("set_reflevel",
		   & VSTSrc::set_reflevel,
           py::arg("reflevel") = 0)
		.def("set_iqrate",
		   & VSTSrc::set_iqrate,
           py::arg("iqrate") = 0);
}







