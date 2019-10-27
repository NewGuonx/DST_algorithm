# Install script for directory: /Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.0.dylib;/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib" TYPE SHARED_LIBRARY FILES
    "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.0.dylib"
    "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.0.dylib"
      "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.1.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libbplustree.1.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib" TYPE SHARED_LIBRARY FILES "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib")
  if(EXISTS "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libbplustree.1.dylib"
      "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib" TYPE STATIC_LIBRARY FILES "/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.a")
  if(EXISTS "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/sonAspy/github_rep/dst_algorithms/btree/bplustree-io/build/lib/libbplustree.a")
  endif()
endif()

