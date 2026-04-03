cmake_minimum_required(VERSION 3.16)

project(cypherApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core)
find_package(OpenSSL REQUIRED)

add_library(backend
    backend/cryption/cryption_main.cpp
    backend/cypher/verify_main.cpp
)

target_link_libraries(backend PRIVATE Qt6::Core)

target_include_directories(backend PUBLIC CryptionEngine)   