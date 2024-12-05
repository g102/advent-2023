#include <fstream>
#include <print>
#include <vector>

#include "../lib/Map.h"
#include "../lib/common.h"
#include "rules.h"

struct Pos {
	size_t row, col;
};

struct Beam {
	Pos p;
	Dir d;
};

struct State {
	std::vector<Beam> beams;
	Map& m, excite;

	State(Map& _m) : m(_m) {
		std::string empty(m.data.size(), ' ');
		excite = Map(empty);
	};

	void spawn_beam(Pos _p, Dir _d) { beams.push_back(Beam{_p, _d}); }

	void next_frame() {
		if (beams.size() != 0) {
			resolve_beams();
			advance_beams();
			cleanup_beams();
			mark_path();
		}
	}

	void resolve_beams() {
		// resolve a beam: determine where it will go for the next frame;
		// this is also where one finds out if the beam splits in two
		for (auto&& b : beams) {
			auto next_dir = next(b.d, m(b.p.row, b.p.col));
			b.d = next_dir[0];

			for (size_t ix = 1; ix < next_dir.size(); ix++)
				spawn_beam(b.p, next_dir[ix]);
		}
	}

	void advance_beams() {
		// advance: knowing the direction is good, move the beam to next tile
		for (auto&& b : beams) {
			if (b.d == N)
				b.p.row--;
			else if (b.d == E)
				b.p.col++;
			else if (b.d == S)
				b.p.row++;
			else
				b.p.col--;
		}
	}

	void cleanup_beams() {
		// if any of the beams are outside the world, delete them
		for (auto it = beams.rbegin(); it != beams.rend(); it++) {
			if ((*it).p.row > m.rows or (*it).p.col > m.cols)
				beams.erase(--(it.base()));
		}
	}

	void mark_path() {
		// mark the position of the beams on the map
	}
};

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");
	Map m(readall(input));
	input.close();

	State s(m);
	s.spawn_beam({0, 0}, E);

	s.next_frame();
	s.next_frame();
	s.next_frame();
	s.next_frame();
	s.next_frame();
	
}
