
include_directories (
   "../../Modules/Basic/inc"
   "../../Modules/Thread/inc"
   "../../Modules/Net/inc"
)

add_executable (TCTestBasic
    testBasic.cpp
)

target_link_libraries(TCTestBasic
    TCNet
    TCMath
    TCThread
    TCBasic
)

set_target_properties(TCTestBasic PROPERTIES FOLDER Tests)

install(TARGETS TCTestBasic 
   RUNTIME DESTINATION ${TC_SYSTEM_BIN_INSTALL_DIR}
   LIBRARY DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
   ARCHIVE DESTINATION ${TC_SYSTEM_LIB_INSTALL_DIR}
   PUBLIC_HEADER DESTINATION include
   COMPONENT Tests
)
