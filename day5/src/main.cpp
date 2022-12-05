#include <algorithm>
#include <fstream>
#include <iostream>

int main()
{
    std::vector<std::string> lines;
    std::vector<std::string> setup_lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    setup_lines.assign(lines.begin(), lines.begin() + 8);
    lines.erase(lines.begin(), lines.begin() + 10);

    std::array<std::string, 9> stacks;

    std::size_t const every_nth_index{4};

    for (std::string const& setup_line : setup_lines) {
        size_t index{0};
        for (int i = 1; i < setup_line.length(); i += every_nth_index) {
            char c{setup_line.at(i)};
            if (c != ' ') {
                stacks[index].push_back(c);
            }
            index++;
        }
    }

    for (auto& stack : stacks) {
        std::reverse(stack.begin(), stack.end());
        std::cout << stack << "\n";
    }

    std::string const space_delimiter{" "};
    std::string const first_delimiter{"m "};
    std::string const target_delimiter{"o "};
    for (std::string const& line : lines) {
        std::string const amount_of_crates{line.substr(5, line.find(space_delimiter))};
        std::string const crate_index{
            line.substr(line.find(first_delimiter) + 2, line.find(space_delimiter))};
        std::string const target_index{line.substr(line.find(target_delimiter) + 2, line.length())};

        std::int32_t nr_crates{std::stoi(amount_of_crates)};
        std::int32_t source_i{std::stoi(crate_index) - 1};
        std::int32_t dest_i{std::stoi(target_index) - 1};

        std::cout << nr_crates << " " << source_i << " " << dest_i << "\n";


        std::string crate_slice{stacks.at(source_i).substr(stacks.at(source_i).size() - nr_crates,
                                static_cast<size_t>(nr_crates))};
        stacks.at(source_i).erase(stacks.at(source_i).size() - nr_crates, nr_crates);

        stacks.at(dest_i).append(crate_slice);
    }

    std::string ans;
    for (auto& stack : stacks) {
        ans += stack.back();
    }

    std::cout << ans << "\n";
    return 0;
}