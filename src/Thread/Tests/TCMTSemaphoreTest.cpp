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
#ifdef HAVE_UNIT_TESTS

#include "TCMTSemaphoreTest.h"

#include "TCMTFactory.h"
#include "TCMTSemaphore.h"
#include "TCTime.h"

#include "TCUnitTestCase.h"

#include "TCNewEnable.h"

namespace TC
{
    namespace MT
    {
        namespace Tests
        {
            class SemaphorePostWaitTest : public Unit::TestCase
            {
            public:
                SemaphorePostWaitTest()
                    :Unit::TestCase("TC::MT::Tests::SemaphorePostWaitTest")
                {
                }

                virtual void Execute()
                {
                    {
                        SemaphorePtr m = Factory::CreateSemaphore(0);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore(1);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Wait());
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore(0);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore(0);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore(0);
                        TCUNIT_ASSERT(m);
                        Time start_time = Time::NowMonotonic();
                        TCUNIT_ASSERT(!m->TryWait(Time::FromMilliSeconds(100)));
                        Time wait_time = Time::SinceMonotonic(start_time);
                        TCUNIT_ASSERT(wait_time >= Time::FromMilliSeconds(90));
                        TCUNIT_ASSERT(wait_time <= Time::FromMilliSeconds(200));
                        TCUNIT_ASSERT(m->Post());
                    }

                }
            };

            class SemaphoreSharedCreateTest : public Unit::TestCase
            {
            public:
                SemaphoreSharedCreateTest()
                    :Unit::TestCase("TC::MT::Tests::SemaphoreSharedCreateTest")
                {
                }

                virtual void Execute()
                {
                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m);
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_WHEN_NOT_EXISTS);
                        TCUNIT_ASSERT(m);
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_WHEN_EXISTS);
                        TCUNIT_ASSERT(!m);
                    }

                    {
                        SemaphorePtr m1 = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m1);
                        SemaphorePtr m2 = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_WHEN_EXISTS);
                        TCUNIT_ASSERT(m2);
                    }

                    {
                        SemaphorePtr m1 = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m1);
                        SemaphorePtr m2 = Factory::CreateSemaphore("SemaphoreSharedCreateTest",
                            0, Factory::CRM_WHEN_NOT_EXISTS);
                        TCUNIT_ASSERT(!m2);
                    }
                }
            };

            class SemaphoreSharedPostWaitTest : public Unit::TestCase
            {
            public:
                SemaphoreSharedPostWaitTest()
                    :Unit::TestCase("TC::MT::Tests::SemaphoreSharedPostWaitTest")
                {
                }

                virtual void Execute()
                {
                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedPostWaitTest",
                            0, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedPostWaitTest",
                            1, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Wait());
                        TCUNIT_ASSERT(m->Post());
                        TCUNIT_ASSERT(m->Wait());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedPostWaitTest",
                            1, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m);
                        TCUNIT_ASSERT(m->Try());
                        TCUNIT_ASSERT(m->Post());
                    }

                    {
                        SemaphorePtr m = Factory::CreateSemaphore("SemaphoreSharedPostWaitTest",
                            0, Factory::CRM_ALWAYS);
                        TCUNIT_ASSERT(m);
                        Time start_time = Time::NowMonotonic();
                        TCUNIT_ASSERT(!m->TryWait(Time::FromMilliSeconds(100)));
                        Time wait_time = Time::SinceMonotonic(start_time);
                        TCUNIT_ASSERT(wait_time >= Time::FromMilliSeconds(90));
                        TCUNIT_ASSERT(wait_time <= Time::FromMilliSeconds(200));
                        TCUNIT_ASSERT(m->Post());
                    }
                }
            };

            SemaphoreSuite::SemaphoreSuite()
                : Unit::TestSuite("TC::MT::Tests::SemaphoreSuite")
            {
                AddTest(new SemaphorePostWaitTest);
                AddTest(new SemaphoreSharedCreateTest);
                AddTest(new SemaphoreSharedPostWaitTest);
            }

        }
    }
}

#endif
