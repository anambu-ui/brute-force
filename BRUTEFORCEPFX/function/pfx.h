#pragma once
#include <string>

bool trykey(const std::string& pfxFile, const std::string& key);
  
void bruteForcePfx(const std::string& pfxFile, const std::string& charset, int maxLength);