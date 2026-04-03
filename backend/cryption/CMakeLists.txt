cmake_minimum_required(VERSION 3.15)

project(FileCryptionProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include directories
include_directories(
    .
    encyptDecrypt
    file_handling
    processManagement
)

configure_file(.env .env COPYONLY)

# source files for main program
set(MAIN_SRC
    cryption_main.cpp
    processManagement/pM.cpp
    file_handling/IO.cpp
    file_handling/ReadFromEnv.cpp
    encyptDecrypt/file_cryption.cpp
)

# source files for file_cryption program
set(CRYPTION_SRC
    encyptDecrypt/file_cryption_main.cpp
    encyptDecrypt/file_cryption.cpp
    file_handling/IO.cpp
    file_handling/ReadFromEnv.cpp
)

# create executables
add_executable(encrypt_decrypt ${MAIN_SRC})
add_executable(file_cryption ${CRYPTION_SRC})

# optional warnings
if(MSVC)
    target_compile_options(encrypt_decrypt PRIVATE /W4)
    target_compile_options(file_cryption PRIVATE /W4)
else()
    target_compile_options(encrypt_decrypt PRIVATE -Wall -g)
    target_compile_options(file_cryption PRIVATE -Wall -g)
endif()