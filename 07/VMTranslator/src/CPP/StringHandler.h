#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <string>
#include <sstream>
#include <vector>

class StringHandler {

public:
    StringHandler();

    std::string removeCharacterAtIndex(std::string removeFrom, char toRemove, int index);
    std::string removeCharacter(std::string removeFrom, char toRemove);
    std::string eraseFromCharacter(std::string eraseFrom, char delimiter);
    std::string removeComments(std::string removeFrom, char toRemove);
    std::string convertToUpper(std::string toConvert);

typedef struct split
{
  enum empties_t { empties_ok, no_empties };
};

std::vector<std::string> split(std::string toSplit, char delimiter, split::empties_t empties = split::empties_ok);

private:

};

#endif