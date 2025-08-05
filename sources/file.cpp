#include "bsl/file.hpp"
#include <fstream>
#include <filesystem>

std::string File::ReadEntire(const std::filesystem::path &filepath){
    std::ifstream t(filepath, std::ios::binary | std::ios::in);
    if(!t.is_open()){
        return {};
    }

    t.seekg(0, std::ios::end);
    std::size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;

}

std::string File::ReadEntire(const std::string& filepath) {
    return File::ReadEntire(std::filesystem::path(filepath));
}

std::string File::ReadEntire(std::string_view filepath) {
    return File::ReadEntire(std::filesystem::path(filepath));
}

void File::WriteEntire(const std::filesystem::path &filepath, std::string_view buffer) {
    if(filepath.has_parent_path())
        std::filesystem::create_directories(filepath.parent_path());

    std::ofstream stream(filepath, std::ios::binary | std::ios::out);
    if(!stream.is_open())
        return;

    stream.write(buffer.data(), buffer.size());
}

void File::WriteEntire(const std::string& filepath, const std::string& buffer) {
    File::WriteEntire(std::filesystem::path(filepath), std::string_view(buffer));
}

void File::WriteEntire(std::string_view filepath, std::string_view buffer) {
    File::WriteEntire(std::filesystem::path(filepath), buffer);
}

std::string File::MakeUniqueFilename(const std::string& filename) {
    namespace fs = std::filesystem;
    fs::path filePath(filename);
    
    if (!fs::exists(filePath))
        return filename;
    
    std::string baseName = filePath.stem().string();
    std::string extension = filePath.extension().string();
    
    int count = 1;
    while (fs::exists(filePath)) {
        filePath = filePath.parent_path() / (baseName + " (" + std::to_string(count) + ")" + extension);
        count++;
    }
    
    return filePath.string();
}


