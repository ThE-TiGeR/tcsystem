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
//  $Id: TCMathChecksum.h,v c0056a2f47c7 2012/07/03 21:05:30 thomas $
//*******************************************************************************

#ifndef _TC_MATH_CHECKSUM_H_
#define _TC_MATH_CHECKSUM_H_

#include "TCSharedPtr.h"

#include <string>

namespace tc
{
namespace math
{
   /**
    * @addtogroup TC_MATH
    * @{
    */

   /**
    * @file
    * @brief This file provides the definition of tc::math::Checksum
    * @author Thomas Goessler
    */

   /**
   * @brief Class defining the interface for calculating checksums
   * With the method Append data can be added to the checksum calculation
   */
   class Checksum
   {
   public:
      virtual ~Checksum() {}

      /**
       * @short Append data for to the checksum value calculation
       * @param data The data to append to the calculation
       * @param len The length of the data to append
       */
      virtual void Append(const uint8_t *data, uint64_t len) = 0;
      
      /** @short Get the calculated hash string */
      virtual std::string GetHashString() const = 0;

      /** @short Get the calculated hash digets */
      virtual std::string GetHashDigets() const = 0;
   };

   /** @brief Shared pointer of an checksum object */
   typedef SharedPtr<Checksum> ChecksumPtr;

   /**
    * @}
    */

} // namespace math
} // namespace tc


#endif //_TC_MATH_CHECKSUM_H_
