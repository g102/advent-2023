#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::vector<T> parse_line(std::string& line) {
	std::vector<T> x;
	std::stringstream ssline{line};
	T temp;
	while (ssline >> temp) {
		x.push_back(temp);
	}
	return x;
}

long binom(long n, long k) {
	k = k < n - k ? k : n - k;
	if (k == 0) {
		return 1;
	}

	return (n * binom(n - 1, k - 1)) / k;
}

std::vector<long> get_solutions(std::vector<long> a) {
	std::vector<long> out(2, 0);  // result

	// build binomial coefficients
	std::vector<long> coeffs(a.size() + 1, 0);
	for (size_t i = 0; i < coeffs.size(); i++) {
		coeffs[i] = binom(a.size(), i);
	}

	// forward solution
	std::vector b = a;
	for (long k = 0; k < a.size(); k++) {
		b[k] *= pow(-1, k + a.size() + 1) * coeffs[k];
	}
	out[0] = std::accumulate(b.begin(), b.end(), 0);

	// backward solution
	b = a;
	for (long k = 0; k < a.size(); k++) {
		b[k] *= pow(-1, k) * coeffs[k+1];
	}
	out[1] = std::accumulate(b.begin(), b.end(), 0);
	
	return out;
}

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	long ctr_part1 = 0;
	long ctr_part2 = 0;
	for (std::string line; getline(input, line);) {
		auto parsed = parse_line<long>(line);
		auto sol = get_solutions(parsed);
		
		ctr_part1 += sol[0];
		ctr_part2 += sol[1];
	}
	std::cout << ctr_part1 << "\n";
	std::cout << ctr_part2 << "\n";
}
