#include <fstream>
#include <print>
#include <ranges>
#include <vector>
#include <cmath>

#include "../lib/Map.h"
#include "../lib/common.h"

struct Sub {
	size_t row, col;
	Sub(std::vector<size_t> sub) : row(sub[0]), col(sub[1]) {}
};

size_t count_between(auto a, auto b,
                     const std::ranges::range auto& x) {
	// how may members of x are between a and b?
	if (a > b) std::swap(a, b);
	auto in_between = [&](auto y) { return y >= a and y < b; };
	return std::ranges::count_if(x, in_between);
}

u_long distance(const Sub& first, const Sub& second, const auto& empty_rows,
                const auto& empty_cols, int added_space = 1) {
	u_long dist = 0;
	dist += std::abs((ssize_t)first.row - (ssize_t)second.row);
	dist += std::abs((ssize_t)first.col - (ssize_t)second.col);
	dist += added_space * count_between(first.row, second.row, empty_rows);
	dist += added_space * count_between(first.col, second.col, empty_cols);
	return dist;
}

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "test.txt"};
	Map m{readall(input)};
	input.close();

	// find and catalog all galaxies
	std::vector<Sub> galxs;
	for (size_t it = 0; true; ) {
		it = m.data.find('#', it);
		if (it == m.data.npos) break;
		galxs.push_back(m.ix2sub(it));
		it++;
	}

	// find out which rows and columns are empty
	std::vector<size_t> empty_rows{}, empty_cols{};
	for (size_t ix = 0; ix < m.rows; ix++) {
		if (std::ranges::find(galxs, ix, &Sub::row) == galxs.end()) {
			empty_rows.push_back(ix);
		}
	}
	for (size_t ix = 0; ix < m.cols; ix++) {
		if (std::ranges::find(galxs, ix, &Sub::col) == galxs.end()) {
			empty_cols.push_back(ix);
		}
	}

	// for each pair, compute the distance between
	const long exp = 1000000-1;
	long ctr_part1{0}, ctr_part2{0};
	for (size_t ix = 0; ix < galxs.size(); ix++) {
		for (size_t iy = ix+1; iy < galxs.size(); iy++) {
			ctr_part1 +=
				distance(galxs[ix], galxs[iy], empty_rows, empty_cols);
			ctr_part2 += 
				distance(galxs[ix], galxs[iy], empty_rows, empty_cols, exp);
		}
	}

	std::print("{} {}\n", ctr_part1, ctr_part2);
}
