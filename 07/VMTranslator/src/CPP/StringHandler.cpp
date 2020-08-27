#include "StringHandler.h"

StringHandler::StringHandler() {

}

std::string StringHandler::removeCharacterAtIndex(std::string removeFrom, char toRemove, int index) {
    if(removeFrom[index] == toRemove)
        removeFrom.erase(index, 1);
    return removeFrom;
}

std::string StringHandler::removeCharacter(std::string removeFrom, char toRemove) {
    for(int i = 0; i < removeFrom.length(); i++)
        if(removeFrom[i] == toRemove)
        {
            removeFrom.erase(i, 1);
            i--;
        }
            
    return removeFrom;
}

std::string StringHandler::removeComments(std::string removeFrom, char toRemove) {
    
    std::string toReturn = removeFrom;
    
    for(int i = 0; i < removeFrom.length(); i++)
        if(removeFrom[i] == toRemove && removeFrom[i + 1] == toRemove)
            toReturn = toReturn.substr(0, i);
    
    return toReturn;
}

std::string StringHandler::eraseFromCharacter(std::string eraseFrom, char delimiter) {
    for(int i = 0; i < eraseFrom.length(); i++)
        if(eraseFrom[i] == delimiter)
            eraseFrom.erase(i, eraseFrom.length() - i);
    
    return eraseFrom;
}

std::string StringHandler::convertToUpper(std::string toConvert){
    for(int i = 0; i < toConvert.length(); i++)
        if(toConvert[i] >= 97 && toConvert[i] <= 122)
            toConvert[i] -= 32;
    
    return toConvert;
}

// Courtesy of SO
std::vector<std::string> StringHandler::split(std::string toSplit, char delimiter, split::empties_t empties)
{
    std::vector<std::string> result;
    result.clear();
    std::istringstream ss( toSplit );
    while (!ss.eof())
    {
        std::string field;
        getline( ss, field, delimiter );
        if ((empties == StringHandler::split::no_empties) && field.empty()) continue;
        result.push_back( field );
    }
    return result;
}