#include <print>
#include "Map.h"

Map::Map(std::string _map) : data(_map) {
	if (*(data.end() - 1) != '\n') {
		data.append(1, '\n');
	}

	rows = std::ranges::count(data, '\n');
	cols = data.length() / rows - 1;
	std::erase(data, '\n');
}

Map Map::transpose() {
	std::string newstr(" ", data.length());
	for (size_t ir = 0; ir < rows; ir++) {
		for (size_t ic = 0; ic < cols; ic++) {
			newstr[ic * rows + ir] = (*this)[ir * cols + ic];
		}
	}

	data = newstr;
	std::swap(rows, cols);
	return (*this);
}

void Map::print() {
	for (size_t ir = 0; ir < rows; ir++)
		std::print("{}\n", std::string_view{(*this).row(ir)});
}
