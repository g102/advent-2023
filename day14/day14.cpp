#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

#include "../lib/Map.h"
#include "../lib/common.h"

int weight_on_north(Map m) {
	int ctr{0};
	for (size_t irow = 0; irow < m.rows; irow++) {
		ctr += std::ranges::count(m.row(irow), 'O') * (m.rows - irow);
	}
	return ctr;
}

void roll_line(std::ranges::view auto x) {
	// to roll north: x = col() / south: x = col() | std::views::reverse
	// to roll west: x = row() / east: x = row() | std::views::reverse

	std::string s{x.begin(), x.end()};
	std::string::iterator it_begin{s.begin()}, it_end{};

	while (it_end != s.end()) {
		it_end = std::find(it_begin, s.end(), '#');
		std::string_view subst{it_begin, it_end};
		std::sort(it_begin, it_end, std::greater());
		it_begin = it_end + 1;
	}

	// assign to original view
	for (size_t ix = 0; ix < x.size(); ix++) {
		x[ix] = s[ix];
	}
}

void roll(Map& m, char dir) {
	using namespace std::views;
	switch (dir) {
		case 'n':
			for (size_t icol : iota(0uz, m.cols)) roll_line(m.col(icol));
			break;
		case 'w':
			for (size_t irow : iota(0uz, m.rows)) roll_line(m.row(irow));
			break;
		case 's':
			for (size_t icol : iota(0uz, m.cols))
				roll_line(m.col(icol) | reverse);
			break;
		case 'e':
			for (size_t irow : iota(0uz, m.rows))
				roll_line(m.row(irow) | reverse);
			break;
	}
}

void cycle(Map& m) {
	roll(m, 'n');
	roll(m, 'w');
	roll(m, 's');
	roll(m, 'e');
}

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	Map m{readall(input)};
	input.close();

	std::vector<std::string> states;
	states.push_back(m.data);

	// part 1:
	roll(m, 'n');
	std::cout << weight_on_north(m) << std::endl;

	// complete the rest of the cycle
	roll(m, 'w');
	roll(m, 's');
	roll(m, 'e');
	states.push_back(m.data);

	// part 2: solve here
	long n{1000000000};
	while (true) {
		cycle(m);
		auto iter = std::ranges::find(states, m.data);
		if (iter != states.end()) {
			// we found a repeat, end it there
			auto period = std::distance(iter, states.end());
			auto start = std::distance(states.begin(), iter);
			auto delta = (n - start) % period;
			m.data = *(iter + delta);
			std::cout << weight_on_north(m) << std::endl;
			break;
		}
		states.push_back(m.data);
	}
}
