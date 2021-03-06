set (TC_SYSTEM_LIB_INSTALL_DIR bin)
set (TC_SYSTEM_BIN_INSTALL_DIR bin)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${TC_SYSTEM_LIB_INSTALL_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${TC_SYSTEM_LIB_INSTALL_DIR})
if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${TC_SYSTEM_BIN_INSTALL_DIR})
endif()

if (BUILD_SHARED_LIBS)
   if (TCSYSTEM_STATIC)
     set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -DTC_COMPILE_STATIC_LIBS")
   endif()
else ()
   set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -DTC_COMPILE_STATIC_LIBS")
endif ()

if (DEFINED TC_USE_MEM_CHECK)
   set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -DTC_USE_MEM_CHECK=${TC_USE_MEM_CHECK}")
endif()

function(list_to_string LIST_IN SEPERATOR STRING_OUT)
    
    set(STRING_VAL "")
    foreach(VAL ${LIST_IN})
        set(STRING_VAL "${STRING_VAL} ${VAL}")
    endforeach()

    set(${STRING_OUT} ${STRING_VAL} PARENT_SCOPE)
endfunction(list_to_string)

function(cleanup_compile_link_flags COMPILE_FLAGS_IN COMPILE_FLAGS_OUT)
    set( COMPILE_FLAGS_LIST ${COMPILE_FLAGS_IN} )
    separate_arguments(COMPILE_FLAGS_LIST)

    list(REMOVE_ITEM COMPILE_FLAGS_LIST "")
    list(REMOVE_DUPLICATES COMPILE_FLAGS_LIST)
    list_to_string("${COMPILE_FLAGS_LIST}" " " "${COMPILE_FLAGS_OUT}")

    set( ${COMPILE_FLAGS_OUT} ${${COMPILE_FLAGS_OUT}} PARENT_SCOPE)

endfunction(cleanup_compile_link_flags)

# set our compiler flags
if (ANDROID)
   string (REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
   string (REPLACE "-fno-rtti" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
   set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -DTCOS_ANDROID -Wall -Wno-multichar -DHAVE_UNIT_TESTS -fvisibility=hidden")
   set (TC_COMPILE_CXXFLAGS "${TC_COMPILE_CFLAGS} -std=c++17 -fexceptions -frtti")
   set (TC_COMPILE_FLAGS_DEBUG "-ggdb -DDEBUG")
   set (TC_COMPILE_FLAGS_RELEASE "-O3 -DNDEBUG")

   set (CATFemHex_EXE_LINK_FLAGS         "")
   set (CATFemHex_EXE_LINK_FLAGS_DEBUG   "")
   set (CATFemHex_EXE_LINK_FLAGS_RELEASE "")
elseif (UNIX)
   if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
      set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -DTCOS_LINUX")
   endif ()

   set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} -fPIC -Wall -Wno-multichar -DHAVE_UNIT_TESTS -fvisibility=hidden")
   set (TC_COMPILE_CXXFLAGS "${TC_COMPILE_CFLAGS} -std=c++17")
   set (TC_COMPILE_FLAGS_DEBUG "-ggdb -DDEBUG")
   set (TC_COMPILE_FLAGS_RELEASE "-O3 -DNDEBUG -flto")

   set (TC_EXE_LINK_FLAGS         "")
   set (TC_EXE_LINK_FLAGS_DEBUG   "-ggdb")
   set (TC_EXE_LINK_FLAGS_RELEASE "-flto")

   set (TC_SHARED_LINK_FLAGS         "-Wl,--no-undefined -pthread")
   set (TC_SHARED_LINK_FLAGS_DEBUG   "-ggdb")
   set (TC_SHARED_LINK_FLAGS_RELEASE "-flto")
elseif (WIN32)
   string(REPLACE "/MTd" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   string(REPLACE "/MT" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   string(REPLACE "/MTd" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
   string(REPLACE "/MT" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
   string(REPLACE "/MTd" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
   string(REPLACE "/MT" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

   set (TC_COMPILE_CFLAGS         "${TC_COMPILE_CFLAGS} /DHAVE_UNIT_TESTS /EHsc /W4 /D_WIN32_WINNT=0x0A00 /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS /Gm- /MP /std:c++17")
   set (TC_COMPILE_FLAGS_DEBUG   "/DDEBUG")
   set (TC_COMPILE_FLAGS_RELEASE "/DNDEBUG /Ox /Ob2 /Ot /Oi /GL /GS- /fp:fast /D_SECURE_SCL=0")
   if (TC_SYSTEM_NO_AVX)
       set (TC_COMPILE_FLAGS_RELEASE "${TC_COMPILE_FLAGS_RELEASE}")
   else()
       set (TC_COMPILE_FLAGS_RELEASE "${TC_COMPILE_FLAGS_RELEASE} /arch:AVX")
   endif()

   if (BUILD_SHARED_LIBS)
      set (TC_COMPILE_FLAGS_DEBUG "${TC_COMPILE_FLAGS_DEBUG} /MDd")
      set (TC_COMPILE_FLAGS_RELEASE "${TC_COMPILE_FLAGS_RELEASE} /MD")
   else ()
      set (TC_COMPILE_FLAGS_DEBUG "${TC_COMPILE_FLAGS_DEBUG} /MDd")
      set (TC_COMPILE_FLAGS_RELEASE "${TC_COMPILE_FLAGS_RELEASE} /MD")
   endif ()
   
   if (TC_NO_UNICODE)
   else()
     set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} /D_UNICODE /DUNICODE")
   endif()

   if (TCSYSTEM_UWP_APP)
     set (TC_COMPILE_CFLAGS "${TC_COMPILE_CFLAGS} /DTC_WINDOWS_UWP")
   else()
   endif()

   set (TC_COMPILE_CXXFLAGS "${TC_COMPILE_CFLAGS}")

   set (TC_EXE_LINK_FLAGS         "")
   set (TC_EXE_LINK_FLAGS_DEBUG   "/debug")
   set (TC_EXE_LINK_FLAGS_RELEASE "/LTCG")

   set (TC_SHARED_LINK_FLAGS         "")
   set (TC_SHARED_LINK_FLAGS_DEBUG   "/debug")
   set (TC_SHARED_LINK_FLAGS_RELEASE "/LTCG")
endif()

set (CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${TC_COMPILE_CXXFLAGS}")
set (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${TC_COMPILE_FLAGS_DEBUG}")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${TC_COMPILE_FLAGS_RELEASE}")

set (CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} ${TC_COMPILE_CFLAGS}")
set (CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} ${TC_COMPILE_FLAGS_DEBUG}")
set (CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} ${TC_COMPILE_FLAGS_RELEASE}")

set (CMAKE_EXE_LINKER_FLAGS         "${CMAKE_EXE_LINKER_FLAGS} ${TC_EXE_LINK_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${TC_EXE_LINK_FLAGS_DEBUG}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${TC_EXE_LINK_FLAGS_RELEASE}")

set (CMAKE_SHARED_LINKER_FLAGS         "${CMAKE_SHARED_LINKER_FLAGS} ${TC_SHARED_LINK_FLAGS}")
set (CMAKE_SHARED_LINKER_FLAGS_DEBUG   "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} ${TC_SHARED_LINK_FLAGS_DEBUG}")
set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${TC_SHARED_LINK_FLAGS_RELEASE}")

cleanup_compile_link_flags("${CMAKE_C_FLAGS}" CMAKE_C_FLAGS)
cleanup_compile_link_flags("${CMAKE_C_FLAGS_DEBUG}" CMAKE_C_FLAGS_DEBUG)
cleanup_compile_link_flags("${CMAKE_C_FLAGS_RELEASE}" CMAKE_C_FLAGS_RELEASE)

cleanup_compile_link_flags("${CMAKE_CXX_FLAGS}" CMAKE_CXX_FLAGS)
cleanup_compile_link_flags("${CMAKE_CXX_FLAGS_DEBUG}" CMAKE_CXX_FLAGS_DEBUG)
cleanup_compile_link_flags("${CMAKE_CXX_FLAGS_RELEASE}" CMAKE_CXX_FLAGS_RELEASE)

cleanup_compile_link_flags("${CMAKE_EXE_LINKER_FLAGS}" CMAKE_EXE_LINKER_FLAGS)
cleanup_compile_link_flags("${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CMAKE_EXE_LINKER_FLAGS_DEBUG)
cleanup_compile_link_flags("${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CMAKE_EXE_LINKER_FLAGS_RELEASE)

cleanup_compile_link_flags("${CMAKE_SHARED_LINKER_FLAGS}" CMAKE_SHARED_LINKER_FLAGS)
cleanup_compile_link_flags("${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CMAKE_SHARED_LINKER_FLAGS_DEBUG)
cleanup_compile_link_flags("${CMAKE_SHARED_LINKER_FLAGS_RELEASE}" CMAKE_SHARED_LINKER_FLAGS_RELEASE)

message(STATUS "----------------- TCSystem Compiler --------------------------------")
message(STATUS "CMAKE_C_COMPILER                  = ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER                = ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_AR                          = ${CMAKE_AR}")
message(STATUS "CMAKE_RANLIB                      = ${CMAKE_RANLIB}")
message(STATUS "----------------- TCSystem Compile Flags ---------------------------")
message(STATUS "CMAKE_CXX_FLAGS                   = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG             = ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE           = ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_C_FLAGS                     = ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_DEBUG               = ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "CMAKE_C_FLAGS_RELEASE             = ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "----------------- TCSystem Exe Link Flags --------------------------")
message(STATUS "CMAKE_EXE_LINKER_FLAGS            = ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS_DEBUG      = ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS_RELEASE    = ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
message(STATUS "----------------- TCSystem Shared Lib Link Flags -------------------")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS         = ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS_DEBUG   = ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS_RELEASE = ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
