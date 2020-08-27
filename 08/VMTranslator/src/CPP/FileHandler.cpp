#include "FileHandler.h"

std::vector<std::string> FileHandler::getFilesInDirectory(std::string directory) {
    std::vector<std::string> toReturn;

    for(const auto & entry : std::filesystem::directory_iterator(directory)) {
        toReturn.push_back(entry.path().string());
    }

    return toReturn;
}