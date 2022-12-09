#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>

int main()
{
    std::vector<std::string> lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    struct Pos {
        std::int32_t x{0};
        std::int32_t y{0};

        Pos(std::int32_t x_, std::int32_t y_) : x{x_}, y{y_} {}
        Pos() : x{0}, y{0} {}

        Pos(Pos const& n)
        {
            x = n.x;
            y = n.y;
        }

        bool operator==(Pos const& other) const { return (x == other.x) && (y == other.y); }

        Pos operator+(Pos const& other) const { return {x + other.x, y + other.y}; }

        bool operator<(Pos const& other) const
        {
            return (x < other.x) || (x == other.x && y < other.y);
        }
    };

    std::set<Pos> tail_visited_squares;

    Pos head{0, 0};
    Pos tail{0, 0};
    tail_visited_squares.insert(tail);

    auto move_tail = [&tail, &head, &tail_visited_squares](const Pos& head_move) {
        head.x += head_move.x;
        head.y += head_move.y;

        auto dx = tail.x - head.x;
        if (abs(dx) > 1) {
            tail.x += head_move.x;
            tail.y = head.y;
        }

        auto dy = tail.y - head.y;
        if (abs(dy) > 1) {
            tail.x = head.x;
            tail.y += head_move.y;
        }

        tail_visited_squares.insert(Pos{tail.x, tail.y});
    };

    for (auto const& line : lines) {
        std::int32_t const len{
            static_cast<std::int32_t>(std::stoi(line.substr(2, line.size() - 2)))};

        for (int i = 0; i < len; ++i) {
            Pos head_move;
            switch (line[0]) {
            case 'L': {
                head_move = Pos{-1, 0};
                break;
            }
            case 'R': {
                head_move = Pos{1, 0};
                break;
            }
            case 'U': {
                head_move = Pos{0, 1};
                break;
            }
            case 'D': {
                head_move = Pos{0, -1};
                break;
            }
            default: {
                std::cout << "Should never happen\n";
                break;
            }
            }

            move_tail(head_move);
        }
    }

    std::cout << tail_visited_squares.size();

    return 0;
}