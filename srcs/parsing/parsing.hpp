#ifndef PARSING_HPP
#define PARSING_HPP

#include "../classes/Object/Object.hpp"
#include <vector>
#include <string>

std::vector<Object> parseObjFile(const std::string &objPath);
void parseMtlFile(std::string path);
#endif