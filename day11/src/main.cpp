#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>

static constexpr std::uint64_t worry_divider{3};

class Monkey {
public:
    enum class Operation_t { multiplication = 0, add, square };

    bool operator<(Monkey& other) const
    {
        return this->m_inspect_counter < other.m_inspect_counter;
    }

    explicit Monkey(std::vector<std::string>& lines) noexcept
    {
        /// First line is unnecessary
        lines.erase(lines.begin());

        std::string starting_items{lines[0].substr(17, lines[0].size() - 17)};
        std::list<uint64_t> items;
        std::size_t pos;
        std::string delim{", "};
        while ((pos = starting_items.find(delim)) != std::string::npos) {
            items.push_back(std::stoll(starting_items.substr(0, pos)));
            starting_items.erase(0, pos + delim.length());
        }
        items.push_back(std::stoll(starting_items.substr(0, pos)));

        m_items = std::move(items);
        lines.erase(lines.begin());

        // Operation
        std::string const op_line{lines.front()};
        if (op_line.find('+') != std::string::npos) {
            m_operation_type = Operation_t::add;
            auto s = op_line.substr(op_line.size() - 2, 2);
            m_operation_amount = std::stoll(s);
        }
        else if (op_line.find("* old") != std::string::npos) {
            m_operation_type = Operation_t::square;
            m_operation_amount = 0;
        }
        else {
            m_operation_type = Operation_t::multiplication;
            auto s = op_line.substr(op_line.size() - 2, 2);
            m_operation_amount = std::stoll(s);
        }
        lines.erase(lines.begin());

        // Test
        std::string const test_line{lines.front()};
        m_rule = std::stoll(test_line.substr(test_line.size() - 2, 2));
        lines.erase(lines.begin());

        // True case
        std::string const true_line{lines.front()};
        m_monkey_true = std::stoll(true_line.substr(true_line.size() - 2, 2));
        lines.erase(lines.begin());

        // False case
        std::string const false_line{lines.front()};
        m_monkey_false = std::stoll(false_line.substr(false_line.size() - 2, 2));
        lines.erase(lines.begin());
    }

    std::uint64_t m_inspect_counter{0};
    std::uint64_t m_rule;
    Operation_t m_operation_type;
    std::uint64_t m_operation_amount;
    std::uint64_t m_monkey_true;
    std::uint64_t m_monkey_false;
    std::list<std::uint64_t> m_items;
};

int main()
{
    std::vector<std::string> lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }

    std::vector<Monkey> monkeys;

    while (true) {
        monkeys.emplace_back(lines);
        if (lines.empty()) {
            break;
        }
        lines.erase(lines.begin());
    }

    std::uint64_t lcm{1};
    for (auto const& monkey : monkeys) {
        lcm = std::lcm(lcm, monkey.m_rule);
    }

    std::uint64_t const num_rounds{10000};

    for (int i = 0; i < num_rounds; ++i) {
        for (auto& monkey : monkeys) {
            auto iter = monkey.m_items.begin();
            while (iter != monkey.m_items.end()) {
                std::uint64_t item = *iter;
                monkey.m_inspect_counter++;

                switch (monkey.m_operation_type) {
                case Monkey::Operation_t::multiplication:
                    item *= monkey.m_operation_amount;
                    break;
                case Monkey::Operation_t::add:
                    item += monkey.m_operation_amount;
                    break;
                case Monkey::Operation_t::square:
                    item *= item;
                    break;
                }
                /// Phew, the item survived. Pt.2: No effect
                item %= lcm;

                if ((item % monkey.m_rule) == 0) {
                    monkeys[monkey.m_monkey_true].m_items.push_back(item);
                }
                else {
                    monkeys[monkey.m_monkey_false].m_items.push_back(item);
                }
                monkey.m_items.erase(iter++);
            }
        }
    }

    for (auto& monkey : monkeys) {
        std::cout << monkey.m_inspect_counter << "\n";
    }
    std::sort(monkeys.begin(), monkeys.end());
    for (auto& monkey : monkeys) {
        std::cout << monkey.m_inspect_counter << "\n";
    }

    std::uint64_t monkey_business{monkeys[monkeys.size() - 1].m_inspect_counter
                                  * monkeys[monkeys.size() - 2].m_inspect_counter};

    std::cout << monkey_business;


    return 0;
}