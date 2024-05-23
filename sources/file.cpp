#include "bsl/file.hpp"
#include <fstream>

std::string ReadEntireFile(const std::string &filepath){
    std::ifstream t(filepath);
    if(!t.is_open()){
        printf("Can't read '%s'\n", filepath.c_str());
        return {};
    }

    t.seekg(0, std::ios::end);
    std::size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;
}

void WriteEntireFile(const std::string &filepath, const std::string &content){
    std::ofstream stream(filepath);
    if(!stream.is_open())
        return (void)printf("Can't write '%s'\n", filepath.c_str());
    stream.write(content.data(), content.size());
}
