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
// Copyright (C) 2003 - 2010 Thomas Goessler. All Rights Reserved. 
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
#include "TCDefines.h"

#ifdef TCOS_WINDOWS

#include "TCMTEventWin32.h"

#include "TCOutput.h"

#include "TCNewEnable.h"

namespace TC
{
   namespace MT
   {
      namespace Impl
      {

         EventWin32::EventWin32(bool manual_reset, bool initial_state)
         {
            m_event = ::CreateEventA(0, manual_reset, initial_state, 0);
         }

         EventWin32::~EventWin32()
         {
            if (m_event)
            {
               ::CloseHandle(m_event);
               m_event = 0;
            }
         }

         bool EventWin32::Wait()
         {
            TCTRACE("TCMT", 100,"...");

            bool state = ::WaitForSingleObject(m_event, INFINITE) == WAIT_OBJECT_0;

            TCTRACE1("TCMT", 100,"%s.", state ? "done" : "failed");

            return state;
         }

         bool EventWin32::Try()
         {
            TCTRACE("TCMT", 100,"...");

            bool state = ::WaitForSingleObject(m_event, 0) == WAIT_OBJECT_0;

            TCTRACE1("TCMT", 100,"%s.", state ? "done" : "failed");

            return state;
         }

         bool EventWin32::TryWait(const Time& timeout)
         {
            // for 0 we just try if set
            if (timeout == Time::Zero())
            {
               return Try();
            }
            // for infinite we wait endless
            else if (timeout == Time::Infinite())
            {
               return Wait();
            }

            TCTRACE1("TCMT", 100, "%" TC_UINT64_FORMAT " ms ...", timeout.ToMilliSeconds());

            bool state = ::WaitForSingleObject(m_event, static_cast<DWORD>(timeout.ToMilliSeconds())) == WAIT_OBJECT_0;

            TCTRACE1("TCMT", 100,"%s.", state ? "done" : "failed");
            return state;
         }

         bool EventWin32::Set()
         {
            return ::SetEvent(m_event) == TRUE;
         }

         bool EventWin32::Reset()
         {
            return ::ResetEvent(m_event) == TRUE;
         }

      } // namespace Impl
   } // namespace MT
} // namespace TC

#endif // TCOS_WINDOWS
