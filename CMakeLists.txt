cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
cmake_policy(VERSION 3.16)

project(XML_GTK VERSION "1.0.0" DESCRIPTION "GTK XML")

set(CMAKE_C_STANDARD 99)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

file(GLOB_RECURSE REMOVE_CMAKE "cmake-build-debug/*")
list(REMOVE_ITEM structure.c
        validate_read.c
        christophe.c
        ${REMOVE_CMAKE})

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
endif (UNIX)

add_executable(start
        main.c
        gtk_functions.c
        structure.c
        validate_read.c
        christophe.c)

TARGET_LINK_LIBRARIES(start ${GTK3_LIBRARIES})

message(STATUS "\n----\nGTK include directories: ${GTK3_INCLUDE_DIRS}\n----\n")

