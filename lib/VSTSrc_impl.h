/* -*- c++ -*- */
/*
 * Copyright 2024 placeholder1.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_VST_VSTSRC_IMPL_H
#define INCLUDED_VST_VSTSRC_IMPL_H

#include <gnuradio/VST/VSTSrc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "niRFSA.h"

/* Maximum length of an niRFSA function name */
#define MAX_FUNCTION_NAME_SIZE 55
/* Maximum size of an error message returned from niRFSA_GetError */
#define MAX_ERROR_DESCRIPTION (IVI_MAX_MESSAGE_BUF_SIZE * 2 + MAX_FUNCTION_NAME_SIZE + 75)


namespace gr {
  namespace VST {

    class VSTSrc_impl : public VSTSrc
    {
     private:
        void configure(void);

     public:
        VSTSrc_impl(char* resname,
                    double iqrate,
                    double carrierFreq,
                    double reflevel);
        ~VSTSrc_impl();

        bool stop();

        void set_carrierFreq(double carrierFreq);
        void set_reflevel(double reflevel);
        void set_iqrate(double iqrate);

        // Where all the action really happens
        int work(
                int noutput_items,
                gr_vector_const_void_star &input_items,
                gr_vector_void_star &output_items
        );

        ViSession session = VI_NULL;
        //NIComplexNumberF32* dataPtr = nullptr;
        niRFSA_wfmInfo _wfmInfo;
        ViStatus error = VI_SUCCESS;
        ViChar errorMessage[MAX_ERROR_DESCRIPTION];
        ViStatus lastErrorCode;

        char* _resname;
        double _iqrate;
        double _carrierFreq;
        double _reflevel;
        bool _param_changed = true;
        bool needReInit = false;
        //int _dataPtr_len = 0;
        unsigned long long int _numberSamples = 0;
        gr::thread::mutex _mutex;
    };

  } // namespace VST
} // namespace gr

#endif /* INCLUDED_VST_VSTSRC_IMPL_H */
