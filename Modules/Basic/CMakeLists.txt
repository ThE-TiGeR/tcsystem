
if (NOT TCSYSTEM_NO_BZIB2)
  find_package(BZip2)
  if (BZIP2_FOUND)
	include_directories(${BZIP2_INCLUDE_DIR})
	add_definitions(-DHAVE_BZIP2)
  endif()
endif()

if (NOT TCSYSTEM_NO_ZLIB)
  find_package(ZLIB)
  if (ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS})
	add_definitions(-DHAVE_ZLIB)
  endif()
endif()

include_directories(inc)

set (TC_BASIC_PUBLIC_HEADER
	inc/TCApplication.h
	inc/TCAssert.h
	inc/TCCodec.h
	inc/TCException.h
	inc/TCOutput.h
	inc/TCDebugNew.h
	inc/TCDefines.h
	inc/TCDelete.h
	inc/TCFactory.h
	inc/TCFile.h
	inc/TCFileName.h
	inc/TCHashTable.h
	inc/TCHeap.h
	inc/TCInterlocked.h
	inc/TCMLSHandler.h
	inc/TCMemoryMappedFile.h
	inc/TCNew.h
	inc/TCNewDisable.h
	inc/TCNewEnable.h
	inc/TCNonCopyable.h
	inc/TCRng.h
	inc/TCScopedPtr.h
	inc/TCScopedArray.h
	inc/TCSharedPtr.h
	inc/TCSharedPtrImpl.h
	inc/TCStream.h
	inc/TCStreamAble.h
	inc/TCString.h
	inc/TCSystem.h
	inc/TCStlAlgorithm.h
	inc/TCStlTypes.h
	inc/TCTime.h
	inc/TCTypes.h
	inc/TCUtil.h
	inc/TCValue.h
	inc/TCWeakPtr.h
	inc/TCWFile.h
	inc/TCWFileName.h
	inc/TCWString.h
	inc/TCUnitApi.h
	inc/TCUnitCleanLiness.h
	inc/TCUnitFailure.h
	inc/TCUnitSimpleTestResult.h
	inc/TCUnitTestCase.h
	inc/TCUnitTest.h
	inc/TCUnitTestResult.h
	inc/TCUnitTestSuite.h
	inc/TCUnitTreeTestResult.h
	inc/TCUnitTreeTestRunner.h
)
if (TCSYSTEM_TESTS)
  set (TEST_FILES
	src/TCUnitSimpleTestResult.cpp
	src/TCUnitTestCase.cpp
	src/TCUnitTestSuite.cpp
	src/TCUnitTreeTestResult.cpp
	src/TCUnitTreeTestRunner.cpp

	tests/TCWStringTest.h
	tests/TCBasicTestSuite.cpp
	tests/TCBasicTestSuite.h
	tests/TCFileNameTest.cpp
	tests/TCFileNameTest.h
	tests/TCHashTableTest.cpp
	tests/TCHashTableTest.h
	tests/TCStreamTest.cpp
	tests/TCStreamTest.h
	tests/TCStringTest.cpp
	tests/TCStringTest.h
	tests/TCTimeTest.cpp
	tests/TCTimeTest.h
	tests/TCUtilTest.cpp
	tests/TCUtilTest.h
	tests/TCWFileNameTest.cpp
	tests/TCWFileNameTest.h
	tests/TCWStringTest.cpp)
endif()

add_library (TCBasic ${TCSYSTEM_LIB_TYPE}
	src/TCApplication.cpp
	src/TCAsciiCodec.cpp
	src/TCAsciiCodec.h
	src/TCBinaryCodec.cpp
	src/TCBinaryCodec.h
	src/TCBz2FileStream.cpp
	src/TCBz2FileStream.h
	src/TCClock.cpp
	src/TCClock.h
	src/TCDebugHeap.cpp
	src/TCDebugHeap.h
	src/TCDebugNew.cpp
	src/TCException.cpp
	src/TCFactory.cpp
	src/TCFile.cpp
	src/TCFileName.cpp
	src/TCFileNameImp.h
	src/TCFilePosix.cpp
	src/TCFileStream.cpp
	src/TCFileStream.h
	src/TCFileWin32.cpp
	src/TCGzFileStream.cpp
	src/TCGzFileStream.h
	src/TCHeapCrtlib.cpp
	src/TCHeapCrtlib.h
	src/TCHeapMutex.h
	src/TCInterlocked.cpp
	src/TCMemoryMappedFilePosix.cpp
	src/TCMemoryMappedFilePosix.h
	src/TCMemoryMappedFileWin32.cpp
	src/TCMemoryMappedFileWin32.h
	src/TCMemoryStream.cpp
	src/TCMemoryStream.h
	src/TCMLSHandler.cpp
	src/TCNew.cpp
	src/TCOutput.cpp
	src/TCRng69069.cpp
	src/TCRng69069.h
	src/TCSettings.cpp
	src/TCSettings.h
	src/TCStreamAble.cpp
	src/TCStreamBase.cpp
	src/TCStreamBase.h
	src/TCString.cpp
	src/TCStringImp.h
	src/TCStringStream.cpp
	src/TCStringStream.h
	src/TCStringTraits.h
	src/TCSystem.cpp
	src/TCTime.cpp
	src/TCUtil.cpp
	src/TCWFile.cpp
	src/TCWFileName.cpp
	src/TCWFileWin32.cpp
	src/TCWstring.cpp
	src/TCWStringTraits.h
	${TC_BASIC_PUBLIC_HEADER}
	${TEST_FILES}

	../../cmake/TCSystemCompileFlags.cmake
	../../cmake/FindFOX.cmake
	../../cmake/FindGLext.cmake
	../../cmake/FindMPG123.cmake
	../../cmake/FindOpenAL.cmake
)

if (MSVC)
   target_link_libraries (TCBasic iphlpapi.lib Secur32.lib)
elseif (ANDROID)
elseif (UNIX)
   target_link_libraries (TCBasic -lrt)
endif ()

if (ZLIB_FOUND)
    target_link_libraries (TCBasic ${ZLIB_LIBRARIES})
endif ()
if (BZIP2_FOUND)
    target_link_libraries (TCBasic ${BZIP2_LIBRARIES})
endif ()

set_target_properties(TCBasic PROPERTIES FOLDER Modules)
set_target_properties(TCBasic PROPERTIES COMPILE_DEFINITIONS "TCBASE_EXPORTS")
set_target_properties(TCBasic PROPERTIES PUBLIC_HEADER "${TC_BASIC_PUBLIC_HEADER}")

if (TCSYSTEM_ENABLE_INSTALL)
    install(TARGETS TCBasic
       RUNTIME DESTINATION ${TC_SYSTEM_BIN_INSTALL_DIR}
       LIBRARY DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
       ARCHIVE DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
       PUBLIC_HEADER DESTINATION include
       COMPONENT Base
    )
endif()
