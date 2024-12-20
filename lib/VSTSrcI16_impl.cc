/* -*- c++ -*- */
/*
 * Copyright 2024 placeholder2.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "VSTSrcI16_impl.h"
#define RESOURCE_NAME_MAX 250
#define BUFFER_DEFAULT 1<<24

namespace gr {
  namespace VST {

    using output_type = short;

    VSTSrcI16::sptr VSTSrcI16::make(char* resname, double iqrate, double carrierFreq, double reflevel)
    {
      return gnuradio::make_block_sptr<VSTSrcI16_impl>(resname, iqrate, carrierFreq, reflevel);
    }


    /*
     * The private constructor
     */
    VSTSrcI16_impl::VSTSrcI16_impl(char* resname,
                                   double iqrate,
                                   double carrierFreq,
                                   double reflevel)
      : gr::sync_block("VSTSrcI16",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
    {
        _resname = (char*)malloc(sizeof(char) * RESOURCE_NAME_MAX);
        strncpy(_resname, resname, RESOURCE_NAME_MAX);
        _iqrate = iqrate;
        _carrierFreq = carrierFreq;
        _reflevel = reflevel;
        _param_changed = true;
   //     _dataPtr_len = 0;
        _numberSamples = 0;
        needReInit = false;
    }

    /*
     * Our virtual destructor.
     */
    VSTSrcI16_impl::~VSTSrcI16_impl()
    {
        printf("destructor called for session: %x\n", session);
        stop();
    }

    bool VSTSrcI16_impl::stop()
    {
        printf("Samples passed: %llu\n", _numberSamples);
        if (session)
            niRFSA_Abort(session);
        printf("aborted session: %x\n", session);
        niRFSA_close(session);
        /*
        if (dataPtr)
            free(dataPtr);
            */
        free(_resname);
        return false;
    }


    void VSTSrcI16_impl::configure(void)
    {
        ViInt32 numberOfSamples = 1000; // not used in continous mode
        gr::thread::scoped_lock lock(_mutex);
        if (session)
            niRFSA_Abort(session);
        niRFSA_close(session);
        /*
        if (dataPtr)
            free(dataPtr);
            */

     //   dataPtr = (NIComplexI16*)malloc(sizeof(NIComplexI16) * BUFFER_DEFAULT);
     //   _dataPtr_len = BUFFER_DEFAULT;

        /* Initialize a session */
        printf("Opening device: %s\n", _resname);
        checkWarn(niRFSA_init(static_cast<ViRsrc>(_resname), VI_TRUE, VI_FALSE, &session));
        printf("Getting session: %x\n", session);

        /* Configure NI-RFSA for a simple IQ acquisition */
        checkWarn(niRFSA_ConfigureRefClock(session, "OnboardClock", 10e6));
        printf("Ref clock set.\n");
        checkWarn(niRFSA_ConfigureReferenceLevel(session, "", _reflevel));
        printf("Ref lvl: %f\n", _reflevel);
        checkWarn(niRFSA_ConfigureAcquisitionType(session, NIRFSA_VAL_IQ));
        checkWarn(niRFSA_ConfigureIQCarrierFrequency(session, "", _carrierFreq));
        printf("Carrier freq: %f\n", _carrierFreq);
        checkWarn(niRFSA_ConfigureNumberOfSamples(
            session, "", VI_FALSE, numberOfSamples)); // continous mode
        checkWarn(niRFSA_ConfigureIQRate(session, "", _iqrate));
        printf("IQrate: %f\n", _iqrate);
        checkWarn(niRFSA_Initiate(session));
        printf("Init session.\n");
    Error:
        if (error < VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("ERROR: Init: %s\n", errorMessage);
        }
        else if (error > VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("WARNING: Init: %s\n", errorMessage);
        }
        _param_changed = false;
        _numberSamples = 0;
    }

    void VSTSrcI16_impl::set_carrierFreq(double carrierFreq)
    {
        gr::thread::scoped_lock lock(_mutex);
        _carrierFreq = carrierFreq;
        checkWarn(niRFSA_Abort(session));
        checkWarn(niRFSA_ConfigureIQCarrierFrequency(session, "", _carrierFreq));
        printf("CB: Carrier freq: %f\n", _carrierFreq);
        checkWarn(niRFSA_Initiate(session));
        //printf("CB: Init session.\n");
    Error:
        if (error < VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("ERROR: CB: %s\n", errorMessage);
        }
        else if (error > VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("WARNING: CB: %s\n", errorMessage);
        }
    }

    void VSTSrcI16_impl::set_reflevel(double reflevel)
    {
        gr::thread::scoped_lock lock(_mutex);
        _reflevel = reflevel;
        checkWarn(niRFSA_Abort(session));
        checkWarn(niRFSA_ConfigureReferenceLevel(session, "", _reflevel));
        printf("CB: Ref lvl: %f\n", _reflevel);
        checkWarn(niRFSA_Initiate(session));
        //printf("CB: Init session.\n");
    Error:
        if (error < VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("ERROR: CB: %s\n", errorMessage);
        }
        else if (error > VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("WARNING: CB: %s\n", errorMessage);
        }
    }

    void VSTSrcI16_impl::set_iqrate(double iqrate)
    {
        gr::thread::scoped_lock lock(_mutex);
        _iqrate = iqrate;
        checkWarn(niRFSA_Abort(session));
        checkWarn(niRFSA_ConfigureIQRate(session, "", _iqrate));
        printf("CB: IQrate: %f\n", _iqrate);
        checkWarn(niRFSA_Initiate(session));
        //printf("CB: Init session.\n");
    Error:
        if (error < VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("ERROR: CB: %s\n", errorMessage);
        }
        else if (error > VI_SUCCESS) {
            niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
            printf("WARNING: CB: %s\n", errorMessage);
        }
    }

    int
    VSTSrcI16_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      auto out = static_cast<output_type*>(output_items[0]);

       if (noutput_items < 2){
           return 0;
       }
      if (noutput_items % 2) {
          //printf("Got odd noutput_items %d\n", noutput_items);
          noutput_items -= 1;
      }
      int nsample = noutput_items / 2;
      if (_param_changed) {
          printf("Param changed, set up VST session.\n");
          configure();
      }
      if (needReInit) {
          //printf("Reinit after error.\n");
          if (session) {
              niRFSA_Abort(session);
              niRFSA_Initiate(session);
          }
          needReInit = false;
          error = 0;
      }
      /*
      if (!dataPtr || nsample > _dataPtr_len) {
          printf("Realloc for %d.\n", nsample);
          if (dataPtr)
              free(dataPtr);
          //Read the complex interleaved IQ data 
          dataPtr = (NIComplexI16*)malloc(sizeof(NIComplexI16) * nsample);
          _dataPtr_len = nsample;
      }
      */
      //dataPtr = static_cast<NIComplexI16*>(static_cast<void*>(out));
      checkWarn(niRFSA_FetchIQSingleRecordComplexI16(session,
          "",
          0,
          nsample,
          10.0, /* seconds */
          static_cast<NIComplexI16*>(static_cast<void*>(out)),
          &_wfmInfo
      ));
  Error:
      if (error < VI_SUCCESS) {
          if(error == 0xfffa5e85){
              printf("U");
          }
          else {
              niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
              printf("ERROR: %x, %s\n", error, errorMessage);
          }
          needReInit = true;
      }
      else if (error > VI_SUCCESS) {
          if (error == 0x5b10b) {
              printf("B");
          }
          else {
              niRFSA_GetError(session, &lastErrorCode, MAX_ERROR_DESCRIPTION, errorMessage);
              printf("WARNING: %x, %s\n", error, errorMessage);
          }
      }
      /*
      memcpy(static_cast<void*>(out), static_cast<void*>(dataPtr), nsample * sizeof(*dataPtr));

      for (int nn = 0; nn < nsample; nn++) {
          out[2 * nn] = dataPtr[nn].real;
          out[2 * nn + 1] = dataPtr[nn].imaginary;
      }
      */
      _numberSamples += noutput_items;
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace VST */
} /* namespace gr */
