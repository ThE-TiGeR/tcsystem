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
//  $Id: TCAudioSoundDataMultitrack.cpp,v c0056a2f47c7 2012/07/03 21:05:30 thomas $
//*******************************************************************************

#include "TCAudioSoundDataMultitrack.h"

#include "TCNewEnable.h"

namespace tc
{
   namespace audio
   {
      SoundDataMultitrack::SoundDataMultitrack()
      {
      }

      SoundDataMultitrack::~SoundDataMultitrack()
      {
      }

      uint64_t SoundDataMultitrack::GetData(uint64_t /*num_bytes*/, uint8_t* /*buffer*/)
      {
         return 0;
      }

      void SoundDataMultitrack::SetToStart()
      {
         Locker lock(this);
         for (std::vector<SoundDataPtr>::iterator it = m_sound_data.begin();
            it != m_sound_data.end(); it++)
         {
            (*it)->SetToStart();
         }
      }

      void SoundDataMultitrack::SetLoopData(bool loop)
      {
         Locker lock(this);
         for (std::vector<SoundDataPtr>::iterator it = m_sound_data.begin();
            it != m_sound_data.end(); it++)
         {
            (*it)->SetLoopData(loop);
         }

         SoundData::SetLoopData(loop);
      }
   }
}
