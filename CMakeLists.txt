cmake_minimum_required(VERSION 3.4)

project(corba-example
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The CORBA IDL files
set(IDL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main/idl/HelloApp.idl)

# The directory where the CORBA source code will be generated
set(CORBA_CODEGEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/target/generated-sources-cxx)

# The generated CORBA source code
set(CORBA_CODEGEN_HEADERS
    ${CORBA_CODEGEN_DIR}/HelloApp.hh)
set(CORBA_CODEGEN_SOURCES
    ${CORBA_CODEGEN_DIR}/HelloAppSK.cc)
set(CORBA_CODEGEN_FILES
    ${CORBA_CODEGEN_HEADERS}
    ${CORBA_CODEGEN_SOURCES})

# Create directory where the CORBA source code will be generated
file(MAKE_DIRECTORY ${CORBA_CODEGEN_DIR})

# Generate the CORBA source code
add_custom_command(
    OUTPUT ${CORBA_CODEGEN_FILES}
    COMMAND omniidl -bcxx ${IDL_FILES}
    DEPENDS ${IDL_FILES}
    WORKING_DIRECTORY ${CORBA_CODEGEN_DIR})

add_executable(client
    ${CORBA_CODEGEN_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cxx/client.cpp)

target_include_directories(client
    PRIVATE ${CORBA_CODEGEN_DIR}
    PRIVATE /usr/include/omniORB4)

target_link_libraries(client
    omniORB4 omnithread)

add_executable(server
    ${CORBA_CODEGEN_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cxx/server.cpp)

target_include_directories(server
    PRIVATE ${CORBA_CODEGEN_DIR}
    PRIVATE /usr/include/omniORB4)

target_link_libraries(server
    omniORB4 omnithread)
