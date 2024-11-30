#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <print>
#include <vector>

#include "../lib/common.h"

typedef std::vector<int> vec;

struct Card {
	int card_id, n_winners, points, instances{1};
	vec lotto_numbers, winning_numbers;

	Card(std::string_view line) {
		std::vector<size_t> it{5, line.find(':') + 1, line.find('|') + 1,
		                       line.npos};

		std::vector<vec> contents;
		for (size_t ix = 0; ix < it.size() - 1; ix++) {
			std::string subs{line.substr(it[ix], it[ix + 1] - it[ix])};
			contents.push_back(string_to_vec<int>(subs));
		}

		card_id = contents[0][0];
		lotto_numbers = contents[1];
		winning_numbers = contents[2];
		compute_winners();
		compute_score();
	}

	void compute_winners() {
		n_winners = std::ranges::count_if(lotto_numbers, [&](int x) {
			return std::ranges::contains(winning_numbers, x);
		});
	}

	void compute_score() {
		if (n_winners == 0)
			points = 0;
		else
			points = pow(2, n_winners - 1);
	}
};

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");

	std::vector<Card> cards;

	for (std::string temp; std::getline(input, temp);) {
		cards.push_back(Card{temp});
	}

	for (auto it = cards.begin(); it != cards.end(); it++) {
		for (auto jj = 0; jj < it->n_winners; jj++) {
			(it + jj + 1)->instances += it->instances;
		}
	}

	vec instances, points;
	std::ranges::transform(cards, std::back_inserter(instances),
	                       &Card::instances);
	std::ranges::transform(cards, std::back_inserter(points), &Card::points);

	auto answer_pt1 = std::accumulate(points.begin(), points.end(), 0);
	auto answer_pt2 = std::accumulate(instances.begin(), instances.end(), 0);

	std::print("{}, {}\n", answer_pt1, answer_pt2);
}
