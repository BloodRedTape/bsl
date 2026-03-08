#include "bsl/file.hpp"
#include <fstream>
#include <filesystem>

std::optional<std::string> File::ReadEntire(const std::filesystem::path &filepath){
    if(!std::filesystem::is_regular_file(filepath)){
        return std::nullopt;
    }

    std::ifstream t(filepath, std::ios::binary | std::ios::in);
    if(!t.is_open()){
        return std::nullopt;
    }

    t.seekg(0, std::ios::end);
    std::size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;

}

bool File::WriteEntire(const std::filesystem::path &filepath, std::string_view buffer, std::optional<std::filesystem::perms> permissions) {
    if(filepath.has_parent_path()){
        std::filesystem::create_directories(filepath.parent_path());
    }

    std::ofstream stream(filepath, std::ios::binary | std::ios::out);
    if(!stream.is_open()){
        return false;
    }

    stream.write(buffer.data(), buffer.size());

    if(!stream)
        return false;
    
    if(permissions){
        std::error_code ec;
        std::filesystem::permissions(filepath, *permissions, std::filesystem::perm_options::replace, ec);

        if(ec)
            return false;
    }

    return true;
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


