#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

enum class BoardState {
    unmarked,
    marked,
};

using field_t = std::pair<int, BoardState>;
using board_t = std::array<std::array<field_t, 5>, 5>;

template <typename T>
std::ostream &operator<<(std::ostream &output, std::vector<T> const &values) {
    output << "[ ";
    for (auto const &value : values)
        output << value << ", ";
    output << "]";
    return output;
}

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &output, std::array<T, N> const &values) {
    output << "[ ";
    for (auto const &value : values)
        output << value << ", ";
    output << "]";
    return output;
}

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &output,
                         std::array<std::array<T, N>, N> const &values) {
    output << "[\n";
    for (auto const &value : values)
        output << value << ",\n";
    output << "]";
    return output;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &output, std::pair<T, U> const &values) {

    output << values.first << ": " << values.second;
    return output;
}

std::ostream &operator<<(std::ostream &output, BoardState const &value) {
    output << (value == BoardState::marked ? "X" : "O");
    return output;
}

std::vector<std::string> readFile(const std::string &path) {
    std::ifstream inFile{path};
    std::vector<std::string> lines{};
    std::string current{};

    while (inFile >> current) {
        lines.push_back(current);
    }

    return lines;
}

std::vector<int> splitNumbers(const std::string &s, char delim) {
    std::vector<int> result;
    std::stringstream ss{s};
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(std::stoi(item));
    }

    return result;
}

bool isWinning(const board_t &board, int j, int k) {
    bool result1{true};
    bool result2{true};

    for (int i{}; i < 5; i++) {
        if (board[j][i].second == BoardState::unmarked)
            result1 = false;
        if (board[i][k].second == BoardState::unmarked)
            result2 = false;
    }
    return (result1 || result2);
}

bool mark(board_t &board, int value) {
    for (int j{}; j < 5; j++) {
        for (int k{}; k < 5; k++) {
            if (board[j][k].first == value) {
                board[j][k].second = BoardState::marked;
                return isWinning(board, j, k);
            }
        }
    }
    return false;
}

int main() {
    std::vector<std::string> lines{};
    lines = readFile("/home/tillb/Projects/advent-of-code/input/day04.input");

    // Randomly drawn numbers
    std::vector<int> randN{splitNumbers(lines[0], ',')};

    // Boards
    std::vector<board_t> boards{};
    auto i{lines.begin()};
    i++;
    while (i != lines.end()) {
        board_t current{};
        for (int j{}; j < 5; j++) {
            for (int k{}; k < 5; k++) {
                current[j][k].first = std::stoi(*i);
                current[j][k].second = BoardState::unmarked;
                i++;
            }
        }
        boards.push_back(current);
    }

    int winningNum{};
    board_t winner;
    std::set<int> foundWinners{};

    for (int num : randN) {
        for (auto &b : boards) {
            if (mark(b, num)) {
                winner = b;
                foundWinners.insert(&b - &boards[0]);
                winningNum = num;
                if (foundWinners.size() == boards.size()) {
                    break;
                }
            }
        }
        if (foundWinners.size() == boards.size()) {
            break;
        }
    }

    std::cout << winner << std::endl;
    std::cout << winningNum << std::endl;

    int score{};
    for (int j{}; j < 5; j++) {
        for (int k{}; k < 5; k++) {
            if (winner[j][k].second == BoardState::unmarked)
                score += winner[j][k].first;
        }
    }
    score *= winningNum;
    std::cout << score << std::endl;

    return 0;
}
