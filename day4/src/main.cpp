#include <algorithm>
#include <fstream>
#include <iostream>

int main()
{
    std::vector<std::string> lines;
    std::uint64_t sum{0};

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    std::string const value_delimiter{"-"};
    std::string const pair_delimiter{","};
    for (std::string const& line : lines) {
        std::string const first_pair{line.substr(0, line.find(pair_delimiter))};
        std::string const second_pair{line.substr(line.find(pair_delimiter) + 1, line.length())};

        int32_t first_min{std::stoi(first_pair.substr(0, first_pair.find(value_delimiter)))};
        int32_t first_max{std::stoi(
            first_pair.substr(first_pair.find(value_delimiter) + 1, first_pair.length()))};

        int32_t second_min{std::stoi(second_pair.substr(0, second_pair.find(value_delimiter)))};
        int32_t second_max{std::stoi(
            second_pair.substr(second_pair.find(value_delimiter) + 1, second_pair.length()))};

        int32_t delta_a{first_max - first_min};
        int32_t delta_b{second_max - second_min};

        if (delta_a < delta_b) {
            std::swap(first_min, second_min);
            std::swap(first_max, second_max);
        }

        if (first_max >= second_min && first_min <= second_max){
            sum++;
        }
    }

    std::cout << sum << "\n";
    return 0;
}