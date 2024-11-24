#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

// TODO: clean this code cause it's FILTHY

typedef std::vector<long long> vec;

bool all_same(std::ranges::range auto x) {
	for (auto it = x.begin() + 1; it != x.end(); it++) {
		if (*it != *x.begin()) {
			return false;
		}
	}
	return true;
}

std::string readall(std::ifstream& file) {
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

size_t count_between(vec x, vec bounds) {
	size_t ctr{0};
	std::ranges::sort(bounds);
	for (auto item : x) {
		if (item >= bounds[0] && item < bounds[1]) {
			ctr++;
		}
	}
	return ctr;
}

struct Map {
	std::string map;
	long long rows, cols;
	vec empty_rows, empty_cols;

	Map(std::string _map) : map(_map) {
		rows = std::ranges::count(map, '\n');
		cols = map.length() / rows - 1;  // -1 removes the "newline" column

		// physically remove the newlines from the string
		auto ret = std::ranges::remove(map, '\n');
		map.erase(ret.begin(), ret.end());

		// make a note of which rows and columns are empty
		(*this).expand_space();
	}

	//  get rows and cols
	auto col(size_t ix) {
		using namespace std::ranges;
		return map | views::drop(ix) | views::stride(cols);
	}

	auto row(size_t ix) {
		using namespace std::ranges;
		return map | views::drop(ix * cols) | views::take(cols);
	}

	void expand_space() {
		// mk2: just keep track of which lines are empty

		for (size_t irow = 0; irow < rows; irow++) {
			if (all_same((*this).row(irow))) {
				empty_rows.push_back(irow);
			}
		}

		for (size_t icol = 0; icol < cols; icol++) {
			if (all_same((*this).col(icol))) {
				empty_cols.push_back(icol);
			}
		}
	}

	long long diff(vec& lhs, vec& rhs, unsigned long empties = 1) {
		auto n_empty_rows_between = count_between(empty_rows, {lhs[0], rhs[0]});
		auto n_empty_cols_between = count_between(empty_cols, {lhs[1], rhs[1]});

		unsigned long distance{0};
		distance = std::abs(lhs[0] - rhs[0]) + std::abs(lhs[1] - rhs[1]) +
		           empties * (n_empty_rows_between + n_empty_cols_between);

		return distance;
	}

	void print() {
		for (size_t ix = 0; ix < rows; ix++) {
			std::cout << std::ranges::to<std::string>((*this).row(ix));
			std::cout << std::endl;
		}
	}
};

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	Map map(readall(input));
	input.close();

	// find and catalog all galaxies
	std::vector<vec> g;
	auto it = map.map.begin() - 1;
	while (true) {
		it = std::find(it + 1, map.map.end(), '#');
		if (it == map.map.end()) {
			break;
		}
		long long d = it - map.map.begin();

		g.push_back({d / map.cols, d % map.cols});
	}

	long long ctr{0};
	for (size_t i0 = 0; i0 < g.size(); i0++) {
		for (size_t i1 = i0 + 1; i1 < g.size(); i1++) {
			ctr += map.diff(g[i0], g[i1], 1000000-1);
		}
	}

	std::cout << ctr << std::endl;
}
