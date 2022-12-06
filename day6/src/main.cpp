#include <algorithm>
#include <fstream>
#include <iostream>

bool check_next(std::string const& s, int i, int n){
    if (n == 0){
        return true;
    }

    for (int j = i + 1; j < i + n; ++j) {
        if (s[i] == s[j]){
            return false;
        }
    }

    return check_next(s, i+1, n-1);
}

int main()
{
    std::vector<std::string> lines;
    std::uint64_t index{0};

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    int n = 14;
    for (std::string const& line : lines) {
        for (int i = 0; i < line.size(); ++i) {
            bool success{check_next(line, i, n)};

            if (success){
                index = i + n;
                break;
            }
        }
    }

    std::cout << index << "\n";
    return 0;
}