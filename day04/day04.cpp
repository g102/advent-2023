#include <algorithm>
#include <cmath>
#include <fstream>
#include <print>
#include <numeric>
#include <sstream>
#include <vector>

#include "../lib/common.h"

typedef std::vector<int> vec;

vec string_to_vec(std::string& s) {
	vec out;
	int temp;
	std::stringstream ss{s};

	while (ss >> temp) {
		out.push_back(temp);
	}

	return out;
}

struct Card {
	int card_id, n_winners, points, instances{1};
	vec lotto_numbers, winning_numbers;

	Card(std::string_view line) {
		std::string_view::iterator it[4];
		it[0] = std::string_view::iterator{&line[3]};
		it[1] = std::ranges::find(line, ':');
		it[2] = std::ranges::find(line, '|');
		it[3] = line.end();

		std::vector<vec> contents;
		for (size_t ix = 0; ix < 3; ix++) {
			std::string temp{it[ix] + 1, it[ix + 1]};
			contents.push_back(string_to_vec(temp));
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
	std::ifstream input = parse_args(argc, argv);

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
	std::ranges::transform(cards, std::back_inserter(instances), &Card::instances);
	std::ranges::transform(cards, std::back_inserter(points), &Card::points);

	auto answer_pt1 = std::accumulate(points.begin(), points.end(), 0);
	auto answer_pt2 = std::accumulate(instances.begin(), instances.end(), 0);

	std::print("{}, {}\n", answer_pt1, answer_pt2);
}
