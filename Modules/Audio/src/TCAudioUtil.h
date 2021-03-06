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
//  $Id: TCAudioUtil.h,v 89939db0b777 2012/09/24 21:17:18 thomas $
//*******************************************************************************
#ifndef _TC_AUDIO_UTIL_H_
#define _TC_AUDIO_UTIL_H_

#include "TCAudioSoundFormat.h"

namespace tc
{
   namespace audio
   {
      namespace util
      {
         inline ALenum SoundFormat2BufferFormat(const SoundFormat& format)
         {
            if (format.GetNumChannels() == 2)
            {
               if (format.GetBitsPerSample() == 8)
               {
                  return AL_FORMAT_STEREO8;
               }
               else if (format.GetBitsPerSample() == 16)
               {
                  return AL_FORMAT_STEREO16;
               }
            }
            else if (format.GetNumChannels() == 1)
            {
               if (format.GetBitsPerSample() == 8)
               {
                  return AL_FORMAT_MONO8;
               }
               else if (format.GetBitsPerSample() == 16)
               {
                  return AL_FORMAT_MONO16;
               }
            }
            else if (format.GetNumChannels() == 6)
            {
               if (format.GetBitsPerSample() == 8)
               {
                  return ::alGetEnumValue("AL_FORMAT_51CHN8");
               }
               else if (format.GetBitsPerSample() == 16)
               {
                  return ::alGetEnumValue("AL_FORMAT_51CHN16");
               }
            }
            else if (format.GetNumChannels() == 8)
            {
               if (format.GetBitsPerSample() == 8)
               {
                  return ::alGetEnumValue("AL_FORMAT_71CHN8");
               }
               else if (format.GetBitsPerSample() == 16)
               {
                  return ::alGetEnumValue("AL_FORMAT_71CHN16");
               }
            }

            return AL_NONE;
         }
      }
   }
}

#endif // _TC_AUDIO_UTIL_H_
