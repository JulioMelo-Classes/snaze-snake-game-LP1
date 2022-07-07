#include "utils.hpp"

#include <vector>
#include <string>

std::vector<std::string> split(std::string str, char separator){
    std::vector<std::string> parts = {};
    size_t begin = 0;
    size_t end = str.find(separator, begin);

    if(str.compare("")==0)
        return parts;

    while(end !=std::string::npos){ // Enquanto encontrar o caractere separador na string.
        parts.push_back(str.substr(begin, end-begin));
        begin = end+1;

        end = str.find(separator, begin);
    }
    parts.push_back(str.substr(begin));

    return parts;
}