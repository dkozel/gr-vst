/* -*- c++ -*- */
/*
 * Copyright 2024 placeholder2.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_VST_VSTSRCI16_H
#define INCLUDED_VST_VSTSRCI16_H

#include <gnuradio/VST/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace VST {

    /*!
     * \brief <+description of block+>
     * \ingroup VST
     *
     */
    class VST_API VSTSrcI16 : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<VSTSrcI16> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of VST::VSTSrcI16.
       *
       * To avoid accidental use of raw pointers, VST::VSTSrcI16's
       * constructor is in a private implementation
       * class. VST::VSTSrcI16::make is the public interface for
       * creating new instances.
       */
      static sptr make(char* resname = "RIO0", double iqrate = 1e6, double carrierFreq = 1e9, double reflevel = 0);
      virtual bool stop() = 0;
      virtual void set_carrierFreq(double carrierFreq = 1e9) = 0;
      virtual void set_reflevel(double reflevel = 0) = 0;
      virtual void set_iqrate(double iqrate = 1e6) = 0;
    };

  } // namespace VST
} // namespace gr

#endif /* INCLUDED_VST_VSTSRCI16_H */
