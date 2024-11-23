#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "../Map.cpp"
#include "../common.h"

int diff(std::ranges::range auto r1, std::ranges::range auto r2) {
	if (std::ranges::equal(r1, r2)) return 0;
	
	int ctr{0};
	for (auto item : std::views::zip(r1, r2)) {
		ctr += std::get<0>(item) != std::get<1>(item);
	}
	return ctr;
}

bool check_symm(Map& m, size_t ix, int must_have_changes = 0) {
	if (ix == 0 || ix == m.rows) {
		return false;
	}

	auto N = ix > (m.rows / 2) ? m.rows - ix : ix;
	auto cumulative_diff{0};
	for (auto i = 0; i < N; i++) {
		cumulative_diff += diff(m.row(ix + i), m.row(ix - (i + 1)));
		if (cumulative_diff > must_have_changes) {
			return false;
		}
	}
	return cumulative_diff == must_have_changes;
}

int get_score(Map& m, int must_have_changes = 0) {
	long score{0};
	for (size_t ir = 0; ir < m.rows; ir++) {
		if (check_symm(m, ir, must_have_changes)) {
			score += ir * 100;
			break;
		}
	}

	m = m.transpose();
	for (size_t ic = 0; ic < m.rows; ic++) {
		if (check_symm(m, ic, must_have_changes)) {
			score += ic;
			break;
		}
	}
	m = m.transpose();
	
	return score;
}

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	std::string in_str = readall(input);
	auto split_str = split(in_str, "\n\n");
	std::vector<Map> maps;
	for (auto&& s : split_str) {
		maps.push_back(Map(s));
	}

	long ctr_pt1{0}, ctr_pt2{0};
	for (auto m : maps) {
		ctr_pt1 += get_score(m, 0);
		ctr_pt2 += get_score(m, 1);
	}

	std::cout << ctr_pt1 << std::endl;
	std::cout << ctr_pt2 << std::endl;
}
