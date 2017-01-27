set ( IPC_LIBRARY_TOP "${CMAKE_SOURCE_DIR}/library/" )

set ( IPC_LIBRARY_SOURCE_LIST
  ${IPC_LIBRARY_TOP}/ipc-channel.c
  ${IPC_LIBRARY_TOP}/ipc-logging.c
  ${IPC_LIBRARY_TOP}/ipc-session.c
  ${IPC_LIBRARY_TOP}/ipc-library-api.c
)

add_library ( ipc-server-library SHARED ${IPC_LIBRARY_SOURCE_LIST} )

target_link_libraries ( ipc-server-library pthread )

install ( TARGETS ipc-server-library DESTINATION lib COMPONENT ipc-server-library )
