#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <vector>
#include <sstream>

template<typename T>
std::vector<T> split(const std::string& input, const std::string& delimiter) {
    std::vector<T> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter[0])) {
        tokens.push_back(static_cast<T>(token));
    }

    return tokens;
}

#endif // SPLIT_H