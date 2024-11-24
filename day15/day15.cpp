#include <fstream>
#include <print>
#include <ranges>
#include <vector>

u_char hash(std::string_view in) {
	u_char out{0};
	for (size_t ix = 0; ix < in.length(); ix++) {
		if (in[ix] == '\n') break;
		out = 17 * (out + in[ix]);
	}
	return out;
}

struct Lens {
	std::string label;
	int focal_length;
};

struct Box {
	u_char label;
	std::vector<Lens> lenses{};

	Box(u_char _label) : label(_label) {}

	void add_lens(std::string& label, short focal_length) {
		auto it = std::ranges::find(lenses, label, &Lens::label);
		if (it != lenses.end()) {
			*it = {label, focal_length};
		} else {
			lenses.push_back({label, focal_length});
		}
	}

	void remove_lens(std::string& label) {
		auto it = std::ranges::find(lenses, label, &Lens::label);
		if (it != lenses.end()) {
			lenses.erase(it);
		}
	}

	int compute_power() {
		int power{0};
		for (auto ix : std::views::iota(0uz, lenses.size())) {
			power += (ix + 1) * lenses[ix].focal_length;
		}
		power *= (label + 1);
		return power;
	}
};

struct Action {
	u_char box_label;
	std::string lens_label;
	int focal_length;

	Action(std::string_view s_in) {
		auto it = std::ranges::find(s_in, '-');
		if (it != s_in.end()) {
			focal_length = 0;
		} else {
			it = std::ranges::find(s_in, '=');
			focal_length = *(it + 1) - '0';
		}
		lens_label = std::string{s_in.begin(), it};
		box_label = hash(lens_label);
	}

	void print() {
		if (focal_length == 0) {
			std::print("Removing lens (id: {}) from box {}\n", lens_label,
			           box_label);
		} else {
			std::print("Adding lens (id: {}, f: {}) to box {}\n", lens_label,
			           focal_length, box_label);
		}
	}
};

int main(int argc, char** argv) {
	std::ifstream input;
	if (argc > 1) {
		input.open(argv[1]);
	} else {
		input.open("test.txt");
	}

	// make the list of boxes (and the result of part 1)
	int ctr_part1{0};
	std::vector<Box> boxes;
	for (std::string temp; std::getline(input, temp, ',');) {
		ctr_part1 += hash(temp);

		Action A{temp};
		auto it = std::ranges::find(boxes, A.box_label, &Box::label);
		if (it == boxes.end()) {
			boxes.push_back(Box{A.box_label});
			it = boxes.end() - 1;
		}

		if (A.focal_length == 0) {
			(*it).remove_lens(A.lens_label);
			if ((*it).lenses.size() == 0) {
				boxes.erase(it);
			}
		} else {
			(*it).add_lens(A.lens_label, A.focal_length);
		}
	}
	input.close();

	int ctr_part2{0};
	for (auto b : boxes) {
		ctr_part2 += b.compute_power();
	}
	std::print("{}, {}\n", ctr_part1, ctr_part2);
}
