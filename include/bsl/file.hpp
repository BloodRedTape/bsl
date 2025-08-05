#pragma once

#include <string>
#include <filesystem>

namespace File{

std::string ReadEntire(const std::filesystem::path &filepath);

std::string ReadEntire(const std::string &filepath);

std::string ReadEntire(std::string_view filepath);

void WriteEntire(const std::filesystem::path &filepath, std::string_view buffer);

void WriteEntire(const std::string &filepath, const std::string &buffer);

void WriteEntire(std::string_view filepath, std::string_view buffer);

std::string MakeUniqueFilename(const std::string& filename);

}//namespace File::
