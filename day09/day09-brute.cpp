#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "../lib/common.h"

bool all_same(std::vector<long> a) {
	using namespace std::ranges;
	for (auto&& item : a)
		if (item != a[0]) return false;
	return true;
}

std::vector<long> diff(std::vector<long> a) {
	std::vector<long> b;
	for (std::tuple d : a | std::ranges::views::pairwise) {
		b.push_back(std::get<1>(d) - std::get<0>(d));
	}
	return b;
}

std::vector<long> next_item(std::ranges::range auto a) {
	if (all_same(a)) {
		a.insert(a.begin(), a[0]);
		a.insert(a.end(), a[0]);
	} else {
		auto b = diff(a);
		b = next_item(b);
		a.insert(a.begin(), a[0] - b[0]);
		a.insert(a.end(), a[a.size() - 1] + b[b.size() - 1]);
	}
	return a;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");

	long ctr_part1{0}, ctr_part2{0};
	for (std::string line; getline(input, line);) {
		auto parsed = string_to_vec<long>(line);
		auto solution = next_item(parsed);
		ctr_part1 += solution[solution.size() - 1];
		ctr_part2 += solution[0];
	}
	std::cout << ctr_part1 << std::endl;
	std::cout << ctr_part2 << std::endl;
}
