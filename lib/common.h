#ifndef _SG_COMMON_H_
#define _SG_COMMON_H_

#include <string>
#include <fstream>
#include <vector>

std::string readall(std::ifstream& file);
std::ifstream parse_args(int argc, char** argv);
std::vector<std::string> split(std::string& input, std::string_view sep);

#endif
