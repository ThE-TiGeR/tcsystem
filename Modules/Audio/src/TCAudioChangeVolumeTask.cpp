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
//  $Id: TCAudioChangeVolumeTask.cpp,v a33a555a5a40 2012/02/01 22:48:18 Thomas $
//*******************************************************************************

#include "TCAudioChangeVolumeTask.h"

#include "TCNewEnable.h"

namespace tc
{
   namespace audio
   {
      ChangeVolumeTask::ChangeVolumeTask(SoundDataPtr sound_data, 
         double start_volume, double end_volume, const Time& duration)
         :ChangeSoundValueTask(sound_data, start_volume, end_volume, duration)
      {
         ApplyNewValueOnSoundData(sound_data, start_volume);
      }

      void ChangeVolumeTask::ApplyNewValueOnSoundData(SoundDataPtr sound_data, double new_volume)
      {
         sound_data->SetVolume(new_volume);
      }
   } // end namespace audio
} // end namespace tc
