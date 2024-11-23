#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string readall(std::ifstream& file) {
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

int main(int argc, char* argv[]) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test-simple.txt");
	}

	std::string map = readall(input);
	input.close();

	auto rows = std::ranges::count(map, '\n');
	auto cols = map.length() / rows;

	std::vector<int> steps(map.length(), -1);

	auto it = std::ranges::find(map, 'S'); // starting point

	// find next by looking around
	

}
