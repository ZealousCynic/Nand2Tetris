#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include<vector>
#include<string>
#include<iostream>
// CPP17
// TODO: Find a way to do this without filesystem
#include<filesystem>

class FileHandler {

public:

    std::vector<std::string> getFilesInDirectory( std::string directory);

private:



};

#endif