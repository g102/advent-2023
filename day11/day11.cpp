#include <fstream>
#include <print>
#include <ranges>
#include <vector>

#include "../lib/Map.h"
#include "../lib/common.h"

typedef std::vector<long long> vec;

bool all_same(const std::ranges::range auto& x) {
	for (auto item : x)
		if (item != x[0]) return false;
	return true;
}

struct Sub {
	size_t row, col;
	Sub(std::vector<size_t> sub) : row(sub[0]), col(sub[1]) {}
};

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "test.txt"};
	Map m{readall(input)};
	input.close();

	// find and catalog all galaxies
	std::vector<Sub> galaxies;
	size_t it = 0;
	while (true) {
		it = m.data.find('#', it);
		if (it == m.data.npos) break;
		galaxies.push_back({m.ix2sub(it)});
		it++;
	}

	// find which rows and columns are empty
	std::vector<size_t> empty_rows{}, empty_cols{};
	for (size_t ix = 0; ix < m.rows; ix++) {
		std::print("{} ", ix);
		if (std::ranges::find(galaxies, ix, &Sub::row) == galaxies.end()) {
			empty_rows.push_back(ix);
		}
	}
	for (size_t ix = 0; ix < m.cols; ix++) {
		if (std::ranges::find(galaxies, ix, &Sub::col) == galaxies.end()) {
			empty_cols.push_back(ix);
		}
	}


}
