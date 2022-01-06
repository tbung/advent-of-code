#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

struct Power {
    int gamma;
    int epsilon;
};

struct LifeSupport {
    int o2;
    int co2;
};

std::vector<std::string> readFile(const std::string &path) {
    std::ifstream inFile{path};
    std::vector<std::string> lines{};
    std::string current{};

    while (inFile >> current) {
        lines.push_back(current);
    }

    return lines;
}

Power part1(const std::vector<std::string> &input) {
    std::string gamma{};
    std::string epsilon{};

    int most_common{};

    for (int i{0}; i < input[0].size(); i++) {
        most_common = std::transform_reduce(
            input.begin(), input.end(), 0, std::plus<int>(),
            [&i](std::string s) { return std::stoi(s.substr(i, 1)); });
        most_common =
            most_common >= (static_cast<int>(input.size()) - most_common);

        gamma.append(std::to_string(most_common));
        epsilon.append(std::to_string(!most_common));
    }

    return Power{std::stoi(gamma, nullptr, 2), std::stoi(epsilon, nullptr, 2)};
}

LifeSupport part2(const std::vector<std::string> &input) {

    std::vector<std::string> vecO2{input};
    std::vector<std::string> vecCO2{input};

    int index{};
    while (vecO2.size() > 1) {
        int most_common{};

        most_common = std::transform_reduce(
            vecO2.begin(), vecO2.end(), 0, std::plus<>(),
            [&index](auto s) { return std::stoi(s.substr(index, 1)); });
        most_common =
            most_common >= (static_cast<int>(vecO2.size()) - most_common);

        std::erase_if(vecO2, [&most_common, &index](auto s) {
            return s.substr(index, 1) != std::to_string(most_common);
        });
        index++;
    }

    index = 0;
    while (vecCO2.size() > 1) {
        int most_common{};

        most_common = std::transform_reduce(
            vecCO2.begin(), vecCO2.end(), 0, std::plus<>(),
            [&index](auto s) { return std::stoi(s.substr(index, 1)); });
        most_common =
            most_common < (static_cast<int>(vecCO2.size()) - most_common);

        std::erase_if(vecCO2, [&most_common, &index](auto s) {
            return s.substr(index, 1) != std::to_string(most_common);
        });
        index++;
    }

    return LifeSupport{std::stoi(vecO2[0], nullptr, 2),
                       std::stoi(vecCO2[0], nullptr, 2)};
}

int main() {
    std::vector<std::string> lines{};
    lines = readFile("/home/tillb/Projects/aoc21/input/day03.input");

    Power power{part1(lines)};
    LifeSupport lifeSupport{part2(lines)};

    std::cout << "Power: " << power.gamma << " | " << power.epsilon
              << std::endl;
    std::cout << "Life Support: " << lifeSupport.o2 << " | "
              << lifeSupport.co2 << std::endl;

    std::cout << "Power Rating: " << power.gamma * power.epsilon << std::endl;
    std::cout << "Life Support Rating: " << lifeSupport.o2 * lifeSupport.co2
              << std::endl;

    return 0;
}
