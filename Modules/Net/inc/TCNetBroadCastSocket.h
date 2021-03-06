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
// see https://bitbucket.org/the____tiger/tcsystem for details.
// Copyright (C) 2003 - 2014 Thomas Goessler. All Rights Reserved. 
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
//  $Id: TCNetBroadCastSocket.h,v 19a9fe061077 2014/07/01 18:05:17 thomas $
//*******************************************************************************

#ifndef _TCNET_BROADCAST_SOCKET_H
#define _TCNET_BROADCAST_SOCKET_H

#include "TCNetSocket.h"
#include "TCNetAddress.h"

namespace tc
{
   namespace net
   {
      /**
      * @addtogroup TC_NET
      * @{
      */

      /**
      * @file
      * @brief This file provides the definition of tc::net::BroadcastReadSocket
      * @author Thomas Goessler
      */

      class BroadcastReadSocket: public Socket
      {
      public:
         /**
         * @brief Reads data from socket
         * @param buffer [out] pointer to a buffer where the data should be written to.
         * @param size [in]  size of \c buffer
         * @param ip [out] in the same format as in_addr.S_un.S_addr
         * @return number of bytes received
         */
         virtual uint64_t ReadBytesFrom(void* buffer, uint64_t size, Address& ip) = 0;

         virtual ~BroadcastReadSocket() {}
      };
      /** Type for an read write socket pointer object */
      typedef SharedPtr<BroadcastReadSocket> BroadcastReadSocketPtr;

      class BroadcastWriteSocket: public Socket
      {
      public:
         /**
         * @brief Writes bytes to the socket
         * @param buffer [out] data which should be sent
         * @param size [in] size of \c buffer
         * @param ip [in] recipient ip address in the same format as in_addr.S_un.S_addr
         * @param port [in] recipient port number
         */
         virtual uint64_t WriteBytesTo(const void* buffer, uint64_t size, const Address& ip, PortNumber port) = 0;

         virtual ~BroadcastWriteSocket() {}
      };
      /** Type for an read write socket pointer object */
      typedef SharedPtr<BroadcastWriteSocket> BroadcastWriteSocketPtr;

      /**
      * @}
      */

   } // namespace net
} // namespace tc

#endif // _TCNET_BROADCAST_SOCKET_H
