set ( IPC_LIBRARY_TOP "${CMAKE_SOURCE_DIR}/library/" )

set ( IPC_LIBRARY_SOURCE_LIST
  ${IPC_LIBRARY_TOP}/ipc-library-api.c
)

add_library ( ipc-server-library SHARED ${IPC_LIBRARY_SOURCE_LIST} )

#target_link_libraries ( ipc-server-library )

install ( TARGETS ipc-server-library DESTINATION lib COMPONENT ipc-server-library )
