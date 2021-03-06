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
//  $Id: TCAudioManager.cpp,v 176932047f05 2013/10/08 20:08:34 thomas $
//*******************************************************************************

#include "TCAudioManager.h"

#include "TCAudioOpenALHandler.h"
#include "TCAudioSoundImp.h"
#include "TCAudioSoundSequenceImp.h"
#include "TCAudioSoundMultitrackImp.h"
#include "TCAudioSoundDataMapper.h"
#include "TCAudioSoundDataWav.h"
#ifdef HAVE_MPG123
#include "TCAudioSoundDataMp3.h"
#endif
#include "TCAudioSoundDataOgg.h"
#include "TCAudioStreamingThread.h"
#include "TCException.h"
#include "TCFactory.h"
#include "TCFileName.h"
#include "TCOutput.h"
#include "TCMTFactory.h"
#include "TCSystem.h"
#include "TCUtil.h"

#include "TCNewEnable.h"

namespace tc
{
   namespace audio
   {
      class ExceptionInitError: public Exception
      {
      public:
         ExceptionInitError(const char* error_string)
            :Exception(error_string)
         {
         }
      };

      class ManagerImp: public Manager
      {
      public:
         ManagerImp();
         virtual ~ManagerImp();

         virtual SoundPtr CreateSound(const std::string&);
         virtual SoundPtr CreateSound(const std::string&, StreamPtr stream);
         virtual SoundCompoundPtr CreateSoundSequence(const std::string& name);
         virtual SoundCompoundPtr CreateSoundMultitrack(const std::string& name);
         virtual void DeleteSound(SoundPtr& sound);
         virtual void DeleteSound(SoundCompoundPtr& sound);

      private:
         multi_threading::ThreadPtr m_streaming_thread;
         StreamingThreadPtr m_streaming_thread_object;
         SoundDataMapperPtr m_sound_data_mapper;
      };

      ManagerImp::ManagerImp()
      {
         OpenALHandlerPtr open_al_handler(new OpenALHandler);
         if (!open_al_handler)
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, new tc::audio::OpenALHandler failed");
         }

         m_streaming_thread_object = StreamingThreadPtr(new StreamingThread(open_al_handler));
         if (!m_streaming_thread_object)
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, new tc::audio::StreamingThread failed");
         }

         m_streaming_thread = multi_threading::factory::CreateThread("TCAudioStreamingThread", 0 , multi_threading::Thread::Priority::HIGH);
         if (!m_streaming_thread)
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, tc::multi_threading::factory::CreateThread(TCAudioStreamingThread) failed");
         }

         if (!m_streaming_thread->Start(m_streaming_thread_object))
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, m_streaming_thread->Start failed");
         }

         if (!m_streaming_thread_object->WaitUntilRunning())
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, m_streaming_thread->WaitUntilRunning failed");
         }

         m_sound_data_mapper = SoundDataMapperPtr(new SoundDataMapper);
         if (!m_sound_data_mapper)
         {
            throw ExceptionInitError("ManagerImp::ManagerImp, new tc::audio::SoundDataMapper failed");
         }
      }

      ManagerImp::~ManagerImp()
      {
         m_streaming_thread_object->Stop();
         m_streaming_thread->Join();
         m_streaming_thread = multi_threading::ThreadPtr();
      }

      SoundPtr ManagerImp::CreateSound(const std::string& file_name)
      {
         try
         {
            CodecPtr codec = factory::CreateLittleEndianBinaryCodec();
            StreamPtr file = factory::CreateFileStream(file_name, Stream::Direction::READ, codec);
            if (!file)
            {
               throw Exception("Open file failed.");
            }

            return CreateSound(file_name::GetName(file_name), file);
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "From file " << file_name << " failed " << e.what());
            return SoundPtr();
         }
      }

      SoundPtr ManagerImp::CreateSound(const std::string& name, StreamPtr stream)
      {
         char  id[5] = {'\0'};
         stream->ReadBytes(4, id);

         SharedPtr<SoundData> sound_data;
         try
         {
            std::string id_string(id);
            if (id_string == "RIFF")
            {
               sound_data = SharedPtr<SoundDataWav>(new tc::audio::SoundDataWav(stream));
            }
            else if (id_string == "OggS")
            {
               sound_data = SharedPtr<SoundDataOgg>(new tc::audio::SoundDataOgg(stream));
            }
            else
            {
#ifdef HAVE_MPG123
               sound_data = SharedPtr<SoundDataMp3>(new tc::audio::SoundDataMp3(stream));
#else
               throw Exception(std::string("Unsupported sound format(") + id + ")");
#endif
            }

            SoundPtr sound (new SoundImp(sound_data, m_streaming_thread_object));
            m_sound_data_mapper->Add(sound, sound_data);

            return sound;
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "From Stream " << name << " failed " << e.what());
            return SoundPtr();
         }
      }

      SoundCompoundPtr ManagerImp::CreateSoundSequence(const std::string&)
      {
         try
         {
            SoundDataSequencePtr sound_data(new SoundDataSequence);
            SoundCompoundPtr sound_sequence(new SoundSequenceImp(sound_data, 
               m_streaming_thread_object, m_sound_data_mapper));

            m_sound_data_mapper->Add(sound_sequence, sound_data);

            return sound_sequence;
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "failed " << e.what());
            return SoundCompoundPtr();
         }
     }

      SoundCompoundPtr ManagerImp::CreateSoundMultitrack(const std::string&)
      {
         try
         {
            SoundDataMultitrackPtr sound_data(new SoundDataMultitrack);
            SoundCompoundPtr sound_multitrack(new SoundMultitrackImp(sound_data, 
               m_streaming_thread_object, m_sound_data_mapper));

            m_sound_data_mapper->Add(sound_multitrack, sound_data);

            return sound_multitrack;
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "failed " << e.what());
            return SoundCompoundPtr();
         }
      }

      void ManagerImp::DeleteSound(SoundPtr& sound)
      {
         if (!sound)
         {
            return;
         }

         try
         {
            sound->Stop();
            m_sound_data_mapper->Remove(sound);
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "failed " << e.what());
         }

         sound = SoundPtr();
      }

      void ManagerImp::DeleteSound(SoundCompoundPtr& sound_c)
      {
         SoundPtr sound = sound_c;
         DeleteSound(sound);

         sound_c = SoundCompoundPtr();
      }

      tc::audio::ManagerPtr Manager::Create()
      {
         try
         {
            return ManagerPtr(new ManagerImp);
         }

         catch (std::exception& e)
         {
            TCERRORS("TCAUDIO", "failed " << e.what());
            return ManagerPtr();
         }
      }
   }
}
