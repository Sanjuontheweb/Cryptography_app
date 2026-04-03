#include <iostream>
#include<string>
#include<fstream>
#include <sstream>
#include "IO.hpp"
#include <filesystem>

namespace fs = std::filesystem;

class ReadEnv {
public:
    std::string getenv() {
        fs::path eenvPath = ".env";
        std::string env_path = eenvPath.string();
        IO io(env_path);
        std::fstream f_stream = io.getFileStream();
        std::stringstream buffer;
        buffer << f_stream.rdbuf();
        std::string content = buffer.str();
        return content;
    }
};