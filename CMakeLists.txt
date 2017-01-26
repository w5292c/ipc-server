cmake_minimum_required ( VERSION 2.8.11 )

project ( ipc-server C )

set (
  IPC_SERVER_VERSION "0.0.1"
)

add_subdirectory ( library )
add_subdirectory ( server )
add_subdirectory ( tests )

# Packaging
set ( CPACK_PACKAGE_VENDOR "Alexander Chumakov" )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "ipc-server - Test server for playing with local IPC" )
set ( CPACK_PACKAGE_VERSION "${IPC_SERVER_VERSION}" )
set ( CPACK_PACKAGE_NAME "ipc-server" )
set ( CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexander Chumakov" )
set ( CPACK_GENERATOR "DEB" )
set ( CPACK_DEB_COMPONENT_INSTALL ON )

set ( CPACK_COMPONENTS_ALL ipc-server ipc-server-library )

include ( CPack )
