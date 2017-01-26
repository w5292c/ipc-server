find_package ( PkgConfig REQUIRED )

include_directories ( ${CMAKE_SOURCE_DIR}/library/ )

set ( IPC_SERVER_TEST_TOP "${CMAKE_SOURCE_DIR}/tests" )

set ( IPC_SERVER_TEST_SOURCE_LIST
  ${IPC_SERVER_TEST_TOP}/main.c
)

add_executable ( ipc-server-test ${IPC_SERVER_TEST_SOURCE_LIST} )

target_link_libraries ( ipc-server-test ipc-server-library )

install ( TARGETS ipc-server-test DESTINATION bin COMPONENT ipc-server-test )
