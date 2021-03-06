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
//  $Id: TCGuiApplication.cpp,v c0056a2f47c7 2012/07/03 21:05:30 thomas $
//*******************************************************************************

#include "TCGuiApplication.h"

#include "TCGuiMessageBox.h"

#include "TCFactory.h"
#include "TCFile.h"
#include "TCFileName.h"
#include "TCGuiImageHandler.h"
#include "TCOutput.h"
#include "TCMLSHandler.h"
#include "TCString.h"
#include "TCUtil.h"

#include "TCNewEnable.h"

namespace tc
{
   namespace gui
   {
      bool RegisterImages(ImageHandler::Ptr img_handler);

      Application::Application()
      {
         m_main_window = 0;
         m_fx_app     = 0;
      }

      bool Application::Init(uint32_t narg, char **argv,
         const std::string &prgName, const std::string &prgVersion, const std::string &company)
      {
         {
            int fxnarg = narg;
            m_fx_app = new FX::FXApp(prgName.c_str(), company.c_str());
            m_fx_app->init(fxnarg, argv);
            narg = fxnarg;
         }

         if (!tc::Application::Init(narg, argv, prgName, prgVersion, company))
         {
            return false;
         }

         if (!ImageHandler::CreatedInstance())
         {
            return false;
         }
         RegisterImages(ImageHandler::GetInstance());

         // Make a tool tip
         new FX::FXToolTip(m_fx_app, 0);
         m_main_window = CreateMainWindow();
         if (!m_main_window)
         {
            TCERRORS("TCGUI", "Faild Creating Main Window");
            return false;
         }

         m_fx_app->create();
         return true;
      }

      bool Application::Run()
      {
         if (m_fx_app)
         {
            return m_fx_app->run() == 0;
         }
         return false;  
      }

      void Application::Exit(int32_t code)
      {
         m_fx_app->reg().writeStringEntry("Version",
            "IdStr", (GetProgrammName() + " " + GetProgrammVersion()).c_str());
         m_fx_app->exit(code);
      }

      Application::~Application()
      {
         ImageHandler::DestroyInstance();
         delete m_fx_app;
      }
   }
}
