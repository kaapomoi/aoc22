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

    std::vector<Pos> rope(10, Pos{});

    auto move_tail = [&rope, &tail_visited_squares](const Pos& head_move) {
        rope[0] = rope[0] + head_move;

        auto sign = [](auto const& d) { return d > 0 ? 1 : -1; };

        for (int i = 1; i < rope.size(); ++i) {
            auto dx = rope[i].x - rope[i - 1].x;
            auto dy = rope[i].y - rope[i - 1].y;

            if (dx == 0 || dy == 0) {
                if (abs(dx) >= 2) {
                    rope[i].x -= sign(dx);
                }
                if (abs(dy) >= 2) {
                    rope[i].y -= sign(dy);
                }
            }
            else if ((abs(dx) != 1) || (abs(dy) != 1)) {
                rope[i].x -= sign(dx);
                rope[i].y -= sign(dy);
            }
        }

        tail_visited_squares.insert(Pos{rope.back().x, rope.back().y});
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