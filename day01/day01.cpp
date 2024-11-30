#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

const std::vector<std::string> dict{"zero", "one", "two",   "three", "four",
                                    "five", "six", "seven", "eight", "nine"};

int parse_digits(std::string_view line) {
	using namespace std::ranges;
	auto digits = iota_view('0', '9' + 1);  // '0', '1', '2', ..., '9'
	int i0 = *(find_first_of(line, digits)) - '0';
	int i1 = *(find_first_of(views::reverse(line), digits)) - '0';

	return i0 * 10 + i1;
}

void replace_dict(std::string& line) {
	for (size_t i = 0; i < line.length(); i++) {
		for (size_t j = 0; j < dict.size(); j++) {
			if (line.substr(i).starts_with(dict[j])) {
				line.replace(i, 1, std::string(1, (char)(j + '0')));
			}
		}
	}
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test-pt2.txt");

	long ctr_pt1{0}, ctr_pt2{0};
	for (std::string line; getline(input, line);) {
		ctr_pt1 += parse_digits(line);
		replace_dict(line);
		ctr_pt2 += parse_digits(line);
	}
	input.close();

	std::cout << ctr_pt1 << std::endl;
	std::cout << ctr_pt2 << std::endl;
}
