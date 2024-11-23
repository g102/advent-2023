#ifndef _SG_MAP_H_
#define _SG_MAP_H_

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

class Map {
   public:
	std::string map;
	size_t rows, cols;

	Map(std::string);

	auto begin() { return map.begin(); }
	auto rbegin() { return map.rbegin(); }
	auto end() { return map.end(); }
	auto rend() { return map.rend(); }

	auto row(size_t ix) {
		return map | std::views::drop(ix * cols) | std::views::take(cols);
	}
	auto col(size_t ix) {
		return map | std::views::drop(ix) | std::views::stride(cols);
	}

	std::vector<size_t> ix2sub(size_t ix) { return {ix / cols, ix % cols}; }
	size_t sub2ix(std::vector<size_t> sub) { return sub[0] * cols + sub[1]; }

	auto& operator[](size_t ix) { return map[ix]; };
	auto& operator()(size_t ir, size_t ic) { return map[sub2ix({ir, ic})]; }

	Map transpose();
	void print();
};

#endif
