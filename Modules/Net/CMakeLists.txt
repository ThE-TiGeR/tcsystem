include (FindOpenSSL)

set (TC_NET_PUBLIC_HEADER
        ${TCSystem_SOURCE_DIR}/inc/TCNetApi.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetAddress.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetBroadCastSocket.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetReadWriteSocket.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetFactory.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetSSLFactory.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetSocket.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetSocketServer.h
        ${TCSystem_SOURCE_DIR}/inc/TCNetTypes.h
)

add_library (TCNet
	TCNetAddress.cpp
	TCNetBase.cpp
	TCNetBase.h
	TCNetDebugNew.cpp
	TCNetFactory.cpp
	TCNetOS.h
	TCNetSocketImp.cpp
	TCNetSocketImp.h
	TCNetSocketServerImp.cpp
	TCNetSocketServerImp.h
	TCNetSSLFactory.cpp
	TCNetSSLSocket.cpp
	TCNetSslSocket.h
	TCNetUtil.cpp
	TCNetUtil.h
	Tests/TCNetAddressTest.cpp
	Tests/TCNetAddressTest.h
	Tests/TCNetTestSuit.cpp
	Tests/TCNetTestSuite.h
	${TC_NET_PUBLIC_HEADER}
)

if (OPENSSL_FOUND)
	include_directories (${OPENSSL_INCLUDE_DIR})
	target_link_libraries (TCNet ${OPENSSL_LIBRARIES})
	set_target_properties(TCNet PROPERTIES COMPILE_DEFINITIONS TCNET_EXPORTS)
else ()
	set_target_properties(TCNet PROPERTIES COMPILE_DEFINITIONS "TCNET_NO_OPENSSL;TCNET_EXPORTS")
endif ()

if (MSVC)
	target_link_libraries (TCNet ws2_32.lib)
endif ()

target_link_libraries(TCNet
    TCThread
    TCBasic
)
add_dependencies(TCNet
    TCThread
    TCBasic
)

set_target_properties(TCNet PROPERTIES FOLDER Modules)
set_target_properties(TCNet PROPERTIES PUBLIC_HEADER "${TC_NET_PUBLIC_HEADER}")

install(TARGETS TCNet
   RUNTIME DESTINATION ${TC_SYSTEM_BIN_INSTALL_DIR}
   LIBRARY DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
   ARCHIVE DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
   PUBLIC_HEADER DESTINATION include
   COMPONENT Networking
)
