#ifndef ENGINE_02_FILESEARCH_H
#define ENGINE_02_FILESEARCH_H

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

using namespace std;

class FileSearch {
public:
    // returns all obj paths inside assets folder
    static std::vector<string> findObjFiles();
};


#endif //ENGINE_02_FILESEARCH_H
