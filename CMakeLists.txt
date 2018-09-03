# Building (out of source build):
# > mkdir build && cd build
# > cmake ..
# > cmake --build .
#
# Testing:
# > ctest -V
#
# Install:
# > cmake --build . --target install

#
#
#   General project setup
#
#
project(mtex2MML)
enable_language(C)
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
cmake_policy(SET CMP0015 NEW)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/astyle.cmake")

include(CheckLibraryExists)
include(GenerateExportHeader)

set(PROJECT_NAME "mtex2MML")
set(LIBRARY "libmtex2MML")
set(STATICLIBRARY "libmtex2MML_static")

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/src/mtex2MML.h" MTEX2MML_HEADER REGEX "^#define MTEX2MML_VERSION \"[^\"]*\"$")

string(REGEX REPLACE "^.*MTEX2MML_VERSION \"([0-9]+).*$" "\\1" MTEX2MML_VERSION_MAJOR "${MTEX2MML_HEADER}")
string(REGEX REPLACE "^.*MTEX2MML_VERSION \"[0-9]+\\.([0-9]+).*$" "\\1" MTEX2MML_VERSION_MINOR  "${MTEX2MML_HEADER}")
string(REGEX REPLACE "^.*MTEX2MML_VERSION \"[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" MTEX2MML_VERSION_REV "${MTEX2MML_HEADER}")
set(MTEX2MML_VERSION_STRING "${MTEX2MML_VERSION_MAJOR}.${MTEX2MML_VERSION_MINOR}.${MTEX2MML_VERSION_REV}")

#
#
#   Installation paths
#
#
set(BIN_INSTALL_DIR bin CACHE PATH "Where to install binaries to.")
set(LIB_INSTALL_DIR lib CACHE PATH "Where to install libraries to.")
set(INCLUDE_INSTALL_DIR include/${PROJECT_NAME} CACHE PATH "Where to install headers to.")

#
#
#   Build options
#
#
option(BUILD_CLAR      "Build Tests using the Clar suite"    ON)

#
#
#   Find required dependencies
#
#
include_directories(src deps ${CMAKE_CURRENT_BINARY_DIR})

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_library(M_LIB m) # only necessary for true *nix systems

#
#
#   Configure Bison/Flex
#
#
set(YYPREFIX mtex2MML_yy)

bison_target(MTEX2MMLPARSER ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c COMPILE_FLAGS "-y -v -p ${YYPREFIX}")
flex_target(MTEX2MMLSCANNER ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c COMPILE_FLAGS "-P ${YYPREFIX}")
add_flex_bison_dependency(MTEX2MMLSCANNER MTEX2MMLPARSER)

#
#
#   Define targets
#
#

# Collect sourcefiles, exclude main.c from libraries
file(GLOB SRC_H ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h deps/uthash/*.h)
file(GLOB SRC_MTEX2MML ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM SRC_MTEX2MML "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

set(PROGRAM "mtex2MML")
set(PROGRAM_SOURCES
  ${SRC_MTEX2MML}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  ${BISON_MTEX2MMLPARSER_OUTPUTS}
  ${FLEX_MTEX2MMLSCANNER_OUTPUTS}
)

add_executable(${PROGRAM} ${PROGRAM_SOURCES})
add_library(${LIBRARY} SHARED
            ${SRC_H}
            ${SRC_MTEX2MML}
            ${BISON_MTEX2MMLPARSER_OUTPUTS}
            ${FLEX_MTEX2MMLSCANNER_OUTPUTS}
)
add_library(${STATICLIBRARY} STATIC
            ${SRC_H}
            ${SRC_MTEX2MML}
            ${BISON_MTEX2MMLPARSER_OUTPUTS}
            ${FLEX_MTEX2MMLSCANNER_OUTPUTS}
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/libmtex2MML.pc.in
${CMAKE_CURRENT_BINARY_DIR}/libmtex2MML.pc @ONLY)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_INSTALL_DIR})
if(NOT $ENV{APPVEYOR} STREQUAL "True")
  install(TARGETS ${LIBRARY} LIBRARY DESTINATION ${LIB_INSTALL_DIR})
  install(TARGETS ${STATICLIBRARY} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
endif()
install(FILES ${SRC_H} DESTINATION ${INCLUDE_INSTALL_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libmtex2MML.pc
  DESTINATION lib/pkgconfig)

if(UNIX AND NOT APPLE AND NOT CYGWIN)
  target_link_libraries(${PROGRAM} ${M_LIB})
  target_link_libraries(${STATICLIBRARY} ${M_LIB})
  target_link_libraries(${LIBRARY} ${M_LIB})
endif()

# Always compile with warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4127 /wd4244 /wd4267 /wd4706 /wd4800 /D_CRT_SECURE_NO_WARNINGS")

  if(DEFINED ENV{APPVEYOR})
    set(CMAKE_GENERATOR_PLATFORM "Visual Studio 12 2013")
  endif()

  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/win32-shims)
elseif(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99 -pedantic-errors -fextended-identifiers ")
endif()

set_target_properties(${LIBRARY} PROPERTIES
  OUTPUT_NAME "mtex2MML"
  SOVERSION ${MTEX2MML_VERSION_STRING}
  VERSION ${MTEX2MML_VERSION_STRING}
)

#
#
#   Rename outputs
#
#
if (MSVC)
  set_target_properties(${STATICLIBRARY} PROPERTIES
    OUTPUT_NAME "mtex2MML_static"
    VERSION ${MTEX2MML_VERSION_STRING}
  )
else()
  set_target_properties(${STATICLIBRARY} PROPERTIES
    OUTPUT_NAME "mtex2MML"
    VERSION ${MTEX2MML_VERSION_STRING}
  )
  # -fPIC, basically
  if (UNIX AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX))
    if ("${CMAKE_VERSION}" VERSION_LESS "2.8.9")
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    else()
      set_target_properties(${STATICLIBRARY} PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
      )
    endif()
  endif()
endif(MSVC)

set_property(TARGET ${LIBRARY}
  APPEND PROPERTY MACOSX_RPATH true
)

generate_export_header(${LIBRARY}
    BASE_NAME ${PROJECT_NAME})

if (MSVC)
  set_property(TARGET ${PROGRAM}
    APPEND PROPERTY LINK_FLAGS /INCREMENTAL:NO
  )
endif(MSVC)

#
#
#   Tests
#
#
if (BUILD_CLAR)
  include (CTest)
  enable_testing()
  find_package(PythonInterp REQUIRED)

  set(CLAR_FIXTURES "${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures/")
  set(CLAR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests")
  add_definitions(-DCLAR_FIXTURE_PATH=\"${CLAR_FIXTURES}\")
	add_definitions(-DCLAR_TMPDIR=\"libmtex2MML_tests\")

  include_directories(${CLAR_PATH})
  file(GLOB_RECURSE SRC_TEST ${CLAR_PATH}/*/*.c ${CLAR_PATH}/*/*.h)
  set(SRC_CLAR "${CLAR_PATH}/main.c" "${CLAR_PATH}/clar.c"
    "${CLAR_PATH}/array.c"
    "${CLAR_PATH}/basic.c"
    "${CLAR_PATH}/cornercases.c"
    "${CLAR_PATH}/delimiters.c"
    "${CLAR_PATH}/env.c"
    "${CLAR_PATH}/functions.c"
    "${CLAR_PATH}/helpers.c"
    "${CLAR_PATH}/maliciousness.c"
    "${CLAR_PATH}/mathjax.c"
    "${CLAR_PATH}/numbered_equations.c"
    "${CLAR_PATH}/performance.c"
    "${CLAR_PATH}/symbols.c"
  )

  add_custom_command(
    OUTPUT ${CLAR_PATH}/clar.suite
    COMMAND ${PYTHON_EXECUTABLE} generate.py
    DEPENDS ${SRC_TEST}
    WORKING_DIRECTORY ${CLAR_PATH}
  )

  set_source_files_properties(
    ${CLAR_PATH}/clar.c
    PROPERTIES OBJECT_DEPENDS ${CLAR_PATH}/clar.suite
  )

  add_executable(mtex2MML_clar ${SRC_H} ${SRC_MTEX2MML} ${SRC_CLAR} ${SRC_TEST}
                ${BISON_MTEX2MMLPARSER_OUTPUTS}
                ${FLEX_MTEX2MMLSCANNER_OUTPUTS}
  )
  if(UNIX AND NOT APPLE AND NOT CYGWIN)
    target_link_libraries(mtex2MML_clar ${M_LIB})
  endif()

  add_custom_command(TARGET mtex2MML_clar
    POST_BUILD
    COMMAND ${PYTHON_EXECUTABLE} mathjax_generate.py
    WORKING_DIRECTORY ${CLAR_PATH}
  )

  add_test(mtex2MML_clar mtex2MML_clar -v)

  if(UNIX)
    # setup valgrind
    add_custom_target(memcheck
      valgrind --leak-check=full --dsymutil=yes --error-exitcode=1 ./mtex2MML_clar  >/dev/null
    )
  endif()
endif ()
