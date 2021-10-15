cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
project(ssh_ssl_cxx)
add_compile_definitions(WITH_OPENSSL)
add_compile_definitions(HAVE_PKCS12_SUPPORT)
include_directories(include)
file(GLOB LIB_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

file(GLOB TEST_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/test/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/test//src/*.c"
)
add_library(ssh_ssl_cxx STATIC ${LIB_SRCS})
set_property(TARGET ssh_ssl_cxx  PROPERTY POSITION_INDEPENDENT_CODE ON)
add_executable(ssh_ssl_cxx_test ${TEST_SRCS})
find_package(OpenSSL 1.1.0 REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
if (WIN32)
  find_package(libssh REQUIRED)
  include_directories(${libssh_DIR}/../../include)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif (WIN32)
target_link_libraries(ssh_ssl_cxx PUBLIC OpenSSL::Crypto)
target_link_libraries(ssh_ssl_cxx PUBLIC OpenSSL::SSL)
target_link_libraries(ssh_ssl_cxx PUBLIC ssh)
target_link_libraries(ssh_ssl_cxx_test ssh_ssl_cxx)

