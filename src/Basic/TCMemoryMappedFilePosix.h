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
#ifndef _TC_MEMORY_MAPPED_FILE_POSIX_H_
#define _TC_MEMORY_MAPPED_FILE_POSIX_H_

#include "TCMemoryMappedFile.h"

namespace TC
{
   /**
   * @addtogroup TC_BASE_IMP
   * @{
   */

   /**
   * @file
   * This header file provides the definition of the class TC::MemoryMappedFilePosix.
   *
   * @author Thomas Goessler
   */

   /**
   * The class TC::MemoryMappedFilePosix is a simple file opener by mapping the file into the memory.
   *
   * @author Thomas Goessler
   */
   class MemoryMappedFilePosix: public MemoryMappedFile
   {
   public:
      MemoryMappedFilePosix();
      virtual ~MemoryMappedFilePosix();

      virtual uint32 GetSize() const;
      virtual uint8* GetData();
      virtual const uint8* GetReadOnlyData() const;

      virtual bool MapToMemory(const std::wstring& fileName,
         bool            readonly,
         uint32          size);
      virtual bool MapToMemory(const std::string& fileName,
         bool            readonly,
         uint32          size);

   private:
      virtual void UnmapFromMemory();

   private:
      /** Size of the mapped data */
      uint32 m_size;
      /** Pointer to the mapped data */
      void* m_data;
      /** Handle of the file */
      int m_file;
      /** Handle of the file mapping */
      void* m_file_map;
      /** File is mapped as readonly or as writeable */
      bool m_readonly;
   };

   /**
   *  @}
   */
}

#endif // _TC_MEMORY_MAPPED_FILE_POSIX_H_
