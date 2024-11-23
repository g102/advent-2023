#include "Map.h"

#include <iostream>

Map::Map(std::string _map) : map(_map) {
	if (*(map.end() - 1) != '\n') {
		map.append(1, '\n');
	}

	rows = std::ranges::count(map, '\n');
	cols = map.length() / rows - 1;

	auto ret = std::ranges::remove(map, '\n');
	map.erase(ret.begin(), ret.end());
};

Map Map::transpose() {
	std::string newstr(" ", map.length());
	for (size_t ir = 0; ir < rows; ir++) {
		for (size_t ic = 0; ic < cols; ic++) {
			newstr[ic * rows + ir] = (*this)[ir * cols + ic];
		}
	}

	map = newstr;
	std::swap(rows, cols);
	return (*this);
}

void Map::print() {
	for (size_t ir = 0; ir < rows; ir++) {
		std::cout << std::string_view(this->row(ir).begin(),
		                              this->row(ir).end())
				  << "\n";
	}
}
