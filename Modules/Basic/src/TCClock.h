//*******************************************************************************
//
// *******   ***   ***               *
//    *     *     *                  *
//    *    *      *                *****
//    *    *       ***  *   *   **   *    **    ***
//    *    *          *  * *   *     *   ****  * * *
//    *     *         *   *      *   * * *     * * *
//    *      ***   ***    *     **   **   **   *   *
//                        *
//*******************************************************************************
// see http://sourceforge.net/projects/tcsystem/ for details.
// Copyright (C) 2003 - 2012 Thomas Goessler. All Rights Reserved. 
//*******************************************************************************
//
// TCSystem is the legal property of its developers.
// Please refer to the COPYRIGHT file distributed with this source distribution.
// 
// This library is free software; you can redistribute it and/or             
// modify it under the terms of the GNU Lesser General Public                
// License as published by the Free Software Foundation; either              
// version 2.1 of the License, or (at your option) any later version.        
//                                                                           
// This library is distributed in the hope that it will be useful,           
// but WITHOUT ANY WARRANTY; without even the implied warranty of            
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         
// Lesser General Public License for more details.                           
//                                                                           
// You should have received a copy of the GNU Lesser General Public          
// License along with this library; if not, write to the Free Software       
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
//*******************************************************************************
//  $Id$
//*******************************************************************************
#ifndef _TC_CLOCK_H_
#define _TC_CLOCK_H_

#include "TCTypes.h"

namespace tc
{
   /**
    * @addtogroup TC_BASE
    * @{
    */

   /**
    * @file
    * @brief This file provides the definition of TCClock
    *
    * @author Thomas Goessler
    */

   /**
    * @brief This class manages frame based time measuring
    *
    * For clarity, this keeps tracks of both real time and virtual time.
    * - System time: real time (zero-based)
    * - Simulation time: virtual time (zero-based)
    * - Frame: current frame
    */
   class TC_DLL_LOCAL Clock
   {
   public:
      Clock();
      ~Clock();

      /** Reset clock to startup conditions */
      void Reset();
      /** Starts collecting the time values */
      void Start();
      /** Stop collecting the time values */
      void Stop();

      /** Get if the clock is running (is collecting the time values */
      inline bool IsRunning() { return m_running; }

      /**
       * Begin a new frame. This method is normally called
       * immediately AFTER rendering the previous frame, and
       * sets the context for all work which will be rendered
       * on the next frame.
       *
       * This method increments the frame count and samples real
       * time to determine the elapsed time since the last frame.
       *
       * <Render frame n>
       * <Begin frame n+1>
       * <Task1>
       * <Task2>
       * <Task3...>
       * <Render frame n+1>
       */
      void BeginFrame();

      /** Get the system time since last reset */
      inline uint64 GetSystem() { Update(); return m_system_time; }
      /** Get time which has been spent for the simulation */
      inline uint64 GetTime() { return m_simulation_time; }

      /** Get the current frame number */
      inline uint64 GetFrame() { return m_frame_count; }
      /** Get the starttime of this frame */
      inline uint64 GetFrameStart() { return m_frame_start_time; }
      /** Get the endtime of this frame which is the starttime for the next frame*/
      inline uint64 GetFrameEnd() { return m_frame_end_time; }

   protected:
      /** updates all time values */
      void Update();

   private:
      bool m_running;
      uint64 m_current_time;
      uint64 m_last_time;

      uint64 m_system_time;
      uint64 m_stop_start_time;

      uint64 m_frame_count;
      uint64 m_frame_start_time;
      uint64 m_frame_end_time;

      uint64 m_simulation_time;
      uint64 m_simulation_offset_time;
   };

   /**
    * @}
    */
}

#endif // _TC_CLOCK_H_
