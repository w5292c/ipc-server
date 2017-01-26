find_package ( PkgConfig REQUIRED )

include_directories ( ${CMAKE_SOURCE_DIR}/library/ )

set ( IPC_SERVER_TOP "${CMAKE_SOURCE_DIR}/server" )

set ( IPC_SERVER_SOURCE_LIST
  ${IPC_SERVER_TOP}/main.c
)

add_executable ( ipc-server ${IPC_SERVER_SOURCE_LIST} )

target_link_libraries ( ipc-server ipc-server-library -pthread )

install ( TARGETS ipc-server DESTINATION bin COMPONENT ipc-server )
