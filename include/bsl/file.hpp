#pragma once

#include <string>
#include <filesystem>
#include <optional>

namespace File{

std::optional<std::string> ReadEntire(const std::filesystem::path &filepath);

bool WriteEntire(const std::filesystem::path &filepath, std::string_view buffer, std::optional<std::filesystem::perms> permissions = std::nullopt);

std::string MakeUniqueFilename(const std::string& filename);

}//namespace File::
