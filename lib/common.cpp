#include "common.h"
#include <sstream>

std::string readall(std::ifstream& file) {
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

std::vector<std::string> split(std::string& input, std::string_view sep) {
	std::vector<std::string> out;
	size_t it = 0;
	while (it != input.npos) {
		it = input.find(sep);
		out.push_back(input.substr(0, it));
		input.erase(0, it + sep.length());
	}
	return out;
}
