#include <fstream>
#include <iostream>

unsigned char hash(std::string_view in) {
	unsigned char out{0};
	for (size_t ix = 0; ix < in.length(); ix++) {
		if (in[ix] == '\n') break;
		out = 17 * (out + in[ix]);
	}
	return out;
}

int main() {
	int ctr{0};
	for (std::string temp{}; std::getline(std::cin, temp, ',');)
		ctr += (int)hash(temp);
	std::cout << ctr << "\n";
}
