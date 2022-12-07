#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <utility>

struct Dir_node {
    std::string node_name;
    std::int64_t size_under_me{0};

    Dir_node* parent{nullptr};
    std::vector<Dir_node*> children{};

    Dir_node(std::string n, Dir_node* parent_node) noexcept
        : node_name{std::move(n)}, parent{parent_node}
    {
    }

    Dir_node* find_with_ptr(Dir_node* n) noexcept
    {
        if (this == n) {
            return this;
        }

        for (auto const child : children) {
            auto res = child->find_with_ptr(n);
            if (res != nullptr) {
                return res;
            }
        }

        return nullptr;
    }
};

bool is_small_enough(Dir_node* dir_node, std::int64_t const max_size)
{
    return dir_node->size_under_me <= max_size;
}

int main()
{
    std::vector<std::string> lines;

    std::ifstream infile("../input.txt");
    std::string l;
    while (std::getline(infile, l)) {
        lines.push_back(l);
    }
    lines.erase(lines.begin());

    std::int64_t max_size{100000};

    std::vector<Dir_node*> all_dirs;
    std::stack<std::string> dir_stack;
    auto* const root_node = new Dir_node("/", nullptr);
    auto current_node = root_node;

    for (std::string const& line : lines) {
        if (line == "$ ls") {
            continue;
        }

        if (line == "$ cd ..") {
            /// Update size
            current_node->parent->size_under_me += current_node->size_under_me;
            current_node = root_node->find_with_ptr(current_node->parent);
            dir_stack.pop();
        }
        else if (line.find("$ cd") != std::string::npos) {
            std::string dir_name{line.substr(5, line.size() - 5)};
            dir_stack.push(current_node->node_name);
            auto finder= [current_node, dir_name]()-> Dir_node* {
                for (auto const child : current_node->children) {
                    if(child->node_name == dir_name){
                        return child;
                    }
                }
                return nullptr;
            };
            current_node = finder();
        }
        else if (line.find("dir ") != std::string::npos) {
            std::string dir_name{line.substr(4, line.size() - 4)};
            auto new_node = new Dir_node(dir_name, current_node);
            current_node->children.push_back(new_node);
            all_dirs.push_back(new_node);
        }
        else {
            size_t index = line.find(' ');
            std::string size_str{line.substr(0, index)};

            std::int64_t file_size{std::stoll(size_str)};

            current_node->size_under_me += file_size;
        }
    }

    std::vector<std::pair<std::string, std::int64_t>> dir_sizes{};
    std::int64_t size_needed{-70000000 + root_node->size_under_me + 30000000};
    std::int64_t total_size_of_small_enough_dirs{0};
    for (auto const& node : all_dirs) {
        std::cout << "Is small enough? Dir: " << node->node_name << ", " << is_small_enough(node, max_size)
                  << "\n";
        if(is_small_enough(node, max_size)){
            total_size_of_small_enough_dirs += node->size_under_me;
        }
        dir_sizes.emplace_back(node->node_name, node->size_under_me);
        std::sort(dir_sizes.begin(), dir_sizes.end());
    }

    auto first_big_enough_dir = std::find_if(dir_sizes.begin(), dir_sizes.end(), [size_needed](auto const& dir)-> bool{
        return dir.second >= size_needed;
    });

    std::cout << total_size_of_small_enough_dirs << "\n";
    std::cout << size_needed << "\n";

    std::cout << first_big_enough_dir->second << "\n";

    return 0;
}