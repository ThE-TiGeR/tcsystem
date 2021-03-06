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
//  $Id: TCNetSSLFactory.cpp,v 19a9fe061077 2014/07/01 18:05:17 thomas $
//*******************************************************************************
#ifndef TCNET_NO_OPENSSL

#include "TCNetSSLFactory.h"

#include "TCNetFactory.h"
#include "TCNetSslSocket.h"

#include "TCNewEnable.h"

namespace tc
{
   namespace net
   {
      namespace ssl_factory
      {
         ReadWriteSocketPtr Connect(const Address& ip_addr, PortNumber port, Protocol protocol)
         {
            SocketPtr socket = factory::Connect(ip_addr, port, protocol);
            if (!socket)
            {
               return ReadWriteSocketPtr();
            }

            SharedPtr<imp::SslSocket> ssl_socket(new imp::SslSocket(socket));
            if (!ssl_socket->Connect())
            {
               return ReadWriteSocketPtr();
            }
            return ssl_socket;
         }
      }
   }
}
#endif