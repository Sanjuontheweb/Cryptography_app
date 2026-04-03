add_library(CryptionEngine
	cypher/verify_main.cpp
	cypher/myevp_key.cpp
	cryption/encyptDecrypt/file_cryption.cpp
	cryption/file_handling/IO.cpp
	cryption/file_handling/ReadFromEnv.cpp
	cryption/processManagement/pM.cpp
	cryption/cryption_main.cpp
)

# Find libraries
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)

# Include directories
target_include_directories(CryptionEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cypher
    ${CMAKE_CURRENT_SOURCE_DIR}/cryption
)

# Link libraries
target_link_libraries(CryptionEngine PUBLIC
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::boost
)