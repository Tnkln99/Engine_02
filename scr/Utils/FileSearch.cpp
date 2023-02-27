#include "FileSearch.h"
#include <iostream>
#include <algorithm>

std::vector<string> FileSearch::findObjFiles() {
    std::string path = "res/models";
    std::vector<string> result;
    for(const auto& p: std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            std::string pathStr = p.path().string();
            if(pathStr.find(".obj") != std::string::npos){
                //std::cout << p.path() << '\n';
                result.push_back(p.path().string());
            }
        }
    }
    for(auto & string : result){
        std::replace( string.begin(), string.end(), '\\', '/'); // replace all 'x' to 'y'
    }
    return result;
}
