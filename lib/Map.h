#ifndef _SG_MAP_H_
#define _SG_MAP_H_

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

class Map {
   public:
	std::string data;
	size_t rows, cols;

	Map(std::string);
	Map transpose();
	void print();

	auto begin() { return data.begin(); }
	auto rbegin() { return data.rbegin(); }
	auto end() { return data.end(); }
	auto rend() { return data.rend(); }

	auto row(size_t ix) {
		return data | std::views::drop(ix * cols) | std::views::take(cols);
	}
	auto col(size_t ix) {
		return data | std::views::drop(ix) | std::views::stride(cols);
	}

	std::vector<size_t> ix2sub(size_t ix) { return {ix / cols, ix % cols}; }
	size_t sub2ix(std::vector<size_t> sub) { return sub[0] * cols + sub[1]; }

	auto& operator[](size_t ix) { return data[ix]; };
	auto& operator()(size_t ir, size_t ic) { return data[sub2ix({ir, ic})]; }

};

#endif
