cmake_minimum_required(VERSION 3.14)

project(c_property_based_testing_example LANGUAGES C VERSION 0.1)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpointer-arith -Wconditional-uninitialized -Wno-unused-parameter -Werror")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(installDir ${CMAKE_CURRENT_BINARY_DIR}/install)
include_directories(${installDir}/usr/local/include)

include(ExternalProject)
ExternalProject_Add(Theft
 URL               https://github.com/silentbicycle/theft/archive/master.tar.gz
 CONFIGURE_COMMAND ""
 BUILD_IN_SOURCE   true
 INSTALL_COMMAND   make install DESTDIR=${installDir}
)
add_library(libtheft STATIC IMPORTED)
set_target_properties(libtheft PROPERTIES
 IMPORTED_LOCATION ${installDir}/usr/local/lib/libtheft.a
)

ExternalProject_Add(Greatest
  URL               https://github.com/silentbicycle/greatest/archive/master.tar.gz
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ${CMAKE_COMMAND} -E make_directory
                      ${installDir}/usr/local/include/
          COMMAND   ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/greatest.h
                      ${installDir}/usr/local/include/
)
add_library(greatest INTERFACE IMPORTED)

add_subdirectory(source)
add_subdirectory(test)
