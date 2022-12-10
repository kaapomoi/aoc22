#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

int main()
{
    std::vector<std::string> lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    std::int64_t reg{1};

    std::vector<int64_t> register_values_at_clock{reg};
    register_values_at_clock.reserve(4000);
    std::size_t index{0};
    std::int64_t screen_width{40};

    auto draw = [&reg, &index, &screen_width]() {
        auto const sprite = {reg - 1, reg, reg + 1};
        if (std::find(sprite.begin(), sprite.end(), index % screen_width) != sprite.end()) {
            std::cout << "#";
        }
        else {
            std::cout << ".";
        }

        if (((index + 1) % screen_width) == 0) {
            std::cout << "\n";
        }
    };

    for (auto const& line : lines) {
        if (line.find("addx ") != std::string::npos) {
            draw();
            register_values_at_clock[index] = reg;
            index++;

            draw();
            register_values_at_clock[index] = reg;
            index++;

            auto number = std::stoll(line.substr(5, line.size() - 5));
            reg += number;
            register_values_at_clock[index] = reg;
        }
        else {
            draw();
            register_values_at_clock[index] = reg;
            index++;
        }
    }

    std::int64_t sum{0};
    for (auto const i : std::vector<std::int64_t>{20, 60, 100, 140, 180, 220}) {
        sum += register_values_at_clock[i - 1] * i;
    }

    std::cout << "\n";
    std::cout << sum;

    return 0;
}