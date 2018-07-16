//
//  EFilesystem.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#pragma once
#include <string>
#include <vector>

namespace EFilesystem {
    std::string readAll(std::string path);
    std::vector<std::string> readLines(std::string path);
    void writeAll(std::string path, std::string data);
    void writeLine(std::string path, std::string data);
};
