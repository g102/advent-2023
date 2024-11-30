#ifndef _SG_COMMON_H_
#define _SG_COMMON_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string readall(std::ifstream& file);
std::vector<std::string> split(std::string& input, std::string_view sep);

template <typename T>
	requires std::integral<T> or std::floating_point<T>
std::vector<T> string_to_vec(std::string& s) {
	std::vector<T> out;
	std::stringstream ss{s};

	for (T temp; ss >> temp;) {
		out.push_back(temp);
	}

	return out;
}

#endif
