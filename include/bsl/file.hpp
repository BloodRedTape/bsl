#pragma once

#include <string>

std::string ReadEntireFile(const std::string &filepath);

void WriteEntireFile(const std::string &filepath, const std::string &buffer);

std::string MakeUniqueFilename(const std::string& filename);

