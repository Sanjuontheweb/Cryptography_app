add_executable(CryptoTests
    test_aes.cpp
)

target_link_libraries(CryptoTests
    CryptoEngine
)