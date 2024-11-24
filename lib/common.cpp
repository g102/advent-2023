#include "common.h"
#include <sstream>

std::string readall(std::ifstream& file) {
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

std::ifstream parse_args(int argc, char** argv) {
	if (argc > 1) {
		return std::ifstream{argv[1]};
	} else {
		return std::ifstream{"test.txt"};
	}
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
