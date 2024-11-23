#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

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

struct Map {
	std::string map;
	size_t rows, cols;

	Map(std::string _map) : map(_map) {
		rows = std::ranges::count(map, '\n');
		auto ret = std::ranges::remove(map, '\n');
		map.erase(ret.begin(), ret.end());
		cols = map.length() / rows;
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

	// add rows and cols
	void add_col(size_t ix) {
		for (ssize_t ii = (rows - 1) * cols + ix; ii > 0; ii -= cols) {
			map.insert(ii, 1, '.');
		}
		cols++;
	}

	void add_row(size_t ix) {
		auto ii = ix * cols;
		map.insert(ii, std::string(cols, '.'));
		rows++;
	}

	void expand_space() {
		for (ssize_t ir = rows - 1; ir >= 0; ir--) {
			if (all_same((*this).row(ir))) {
				(*this).add_row(ir);
			}
		}

		for (ssize_t ic = cols - 1; ic >= 0; ic--) {
			if (all_same((*this).col(ic))) {
				(*this).add_col(ic);
			}
		}
	}

	void print() {
		for (size_t ix = 0; ix < rows; ix++) {
			std::cout << std::ranges::to<std::string>((*this).row(ix));
			std::cout << std::endl;
		}
	}
};

typedef std::pair<ssize_t, ssize_t> pair;
size_t diff(pair lhs, pair rhs) {
	return std::abs(std::get<0>(lhs) - std::get<0>(rhs)) +
	       std::abs(std::get<1>(lhs) - std::get<1>(rhs));
}

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	Map map(readall(input));
	input.close();

	map.expand_space();

	// find and catalog all galaxies
	std::vector<pair> g;
	auto it = map.map.begin() - 1;
	while (true) {
		it = std::find(it + 1, map.map.end(), '#');
		if (it == map.map.end()) {
			break;
		}
		auto d = it - map.map.begin();
		g.push_back({d / map.cols, d % map.cols});
	}

	map.print();

	long ctr{0};
	for (size_t i0 = 0; i0 < g.size(); i0++) {
		for (size_t i1 = i0 + 1; i1 < g.size(); i1++) {
			ctr += diff(g[i0], g[i1]);
		}
	}

	std::cout << ctr << std::endl;
}
