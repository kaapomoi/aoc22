#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>

int main()
{
    std::vector<std::string> lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    std::vector<std::vector<std::int8_t>> trees;

    for (auto const& line : lines) {
        std::vector<std::int8_t> tree_line(line.size(), -1);
        for (std::size_t i = 0; i < line.size(); i++) {
            tree_line.at(i) = static_cast<std::int8_t>(line.at(i) - '0');
        }
        trees.push_back(tree_line);
    }

    std::uint64_t highest_scenic_score{0};

    for (int j = 0; j < trees.size(); ++j) {
        for (int i = 0; i < trees.at(j).size(); ++i) {
            auto const height = trees[j][i];
            std::uint64_t scenic_score{1};

            for (auto [x, y] : std::vector<std::pair<std::size_t, std::size_t>>{
                     {-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                auto ni = x + i;
                auto nj = y + j;

                std::uint64_t tree_count{0};
                while (ni < trees[j].size() && nj < trees.size()) {
                    tree_count++;
                    if (trees[nj][ni] >= height) {
                        break;
                    }
                    ni += x;
                    nj += y;
                }
                scenic_score *= tree_count;
            }
            highest_scenic_score = std::max(scenic_score, highest_scenic_score);
        }
    }

    std::cout << highest_scenic_score;

    return 0;
}