#include <algorithm>
#include <fstream>
#include <iostream>

int main()
{
    std::vector<std::string> lines;
    std::uint64_t sum{0};

    std::ifstream infile("../input.txt");
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i += 3) {
        std::string first{lines.at(i)};
        std::string second{lines.at(i+1)};
        std::string third{lines.at(i+2)};

        for (char const& c : first) {
            auto iter = std::find(second.begin(), second.end(), c);
            auto iter_b = std::find(third.begin(), third.end(), c);

            if (iter != second.end() && iter_b != third.end()){
                char ans = (*iter);
                if (ans > 'A' && ans <= 'Z') {
                    sum += ans - 38;
                }
                else {
                    sum += ans - 96;
                }
                break;
            }
        }
    }

    std::cout << sum << "\n";
    return 0;
}