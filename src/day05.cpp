#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

using irange_t = std::ranges::iota_view<int, int>;

class Fissure {
  public:
    irange_t x;
    irange_t y;
    std::pair<int, int> x_;
    std::pair<int, int> y_;

    static Fissure from_string(const std::string &s);

    bool is_diagonal() {
        if (x.front() == x.back())
            return false;

        if (y.front() == y.back())
            return false;

        return true;
    }

    bool is_45() {
        return (std::abs(x.front() - x.back()) ==
                std::abs(y.front() - y.back()));
    }

    Fissure(std::pair<int, int> a_x, std::pair<int, int> a_y) {
        x = std::views::iota(std::min(a_x.first, a_x.second), std::max(a_x.first, a_x.second) + 1);
        y = std::views::iota(std::min(a_y.first, a_y.second), std::max(a_y.first, a_y.second) + 1);
        x_ = a_x;
        y_ = a_y;
    }

    Fissure(const std::string &s) { *this = from_string(s); }
};

Fissure Fissure::from_string(const std::string &s) {
    std::string delim{" -> "};
    int i = s.find(delim);
    std::string start{s.substr(0, i)};
    std::string end{s.substr(i + delim.length(), s.npos)};

    int x1{}, y1{}, x2{}, y2{};

    x1 = std::stoi(start.substr(0, start.find(",")));
    y1 = std::stoi(start.substr(start.find(",") + 1, start.npos));
    x2 = std::stoi(end.substr(0, end.find(",")));
    y2 = std::stoi(end.substr(end.find(",") + 1, end.npos));

    return Fissure{std::pair<int, int>{x1, x2}, std::pair<int, int>{y1, y2}};
}

std::ostream &operator<<(std::ostream &output, Fissure const &f) {
    output << f.x.front() << "," << f.y.front() << " -> " << f.x.back() << ","
           << f.y.back();
    return output;
}

std::vector<std::string> readFile(const std::string &path) {
    std::ifstream inFile{path};
    std::vector<std::string> lines{};
    std::string current{};

    while (std::getline(inFile, current))
        lines.push_back(current);

    return lines;
}

int main() {
    std::vector<std::string> lines{};
    lines = readFile("/home/tillb/Projects/aoc21/input/day05.input");

    std::vector<Fissure> fissures{};
    for (auto line : lines) {
        Fissure current{line};
        fissures.push_back(current);
    }

    std::size_t max_x{};
    std::size_t max_y{};

    std::ranges::for_each(fissures, [&max_x, &max_y](const auto &f) {
        if (max_x < f.x.back())
            max_x = f.x.back();
        if (max_y < f.y.back())
            max_y = f.y.back();
    });

    std::vector<std::vector<int>> board{max_x + 1, std::vector<int>(max_y + 1)};

    int count{};

    std::ranges::for_each(
        fissures | std::views::filter([](auto f) { return !f.is_diagonal(); }),
        [&count, &board](const auto &f) {
            std::cout << f << "\n";
            for (auto x : f.x) {
                for (auto y : f.y) {
                    board[x][y]++;
                    if (board[x][y] == 2)
                        count++;
                }
            }
        });

    std::ranges::for_each(
        fissures | std::views::filter([](auto f) { return f.is_45(); }),
        [&count, &board](const auto &f) {
            std::cout << f << "\n";
            for (auto x{f.x_.first}, y{f.y_.first};
                 x != f.x_.second, y != f.y_.second; f.x_.first < f.x_.second ? x++ : x--, f.y_.first < f.y_.second ? y++ : y--) {
                board[x][y]++;
                if (board[x][y] == 2)
                    count++;
            }
        });

    std::cout << count << std::endl;

    return 0;
}
