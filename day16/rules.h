#ifndef DAY16_RULES
#define DAY16_RULES

#include <map>

enum Dir { N, E, S, W };

std::vector<Dir> next(const Dir& d, const char tile) {
	if (tile == '.') {
		return {d};
	}

	if (tile == '-') {
		if ((d == E or d == W)) {
			return {d};
		}
	} else {
		return {E, W};
	}

	if (tile == '|') {
		if ((d == N or d == S)) {
			return {d};
		}
	} else if (tile == '|') {
		return {N, S};
	}

	switch (d) {
		case N:
			return (tile == '/' ? std::vector<Dir>{E} : std::vector<Dir>{W});
		case S:
			return (tile == '/' ? std::vector<Dir>{W} : std::vector<Dir>{E});
		case E:
			return (tile == '/' ? std::vector<Dir>{N} : std::vector<Dir>{S});
		case W:
			return (tile == '/' ? std::vector<Dir>{S} : std::vector<Dir>{N});
	}
}

#endif
