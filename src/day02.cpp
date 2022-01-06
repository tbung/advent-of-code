#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <array>

void updatePos(const std::string& direction, const int& count, std::array<int, 2>& pos) {
    if(direction == "forward") {
        pos[0] += count;
    } else if(direction == "up") {
        pos[1] -= count;
    } else if(direction == "down") {
        pos[1] += count;
    }
}

void updatePos(const std::string& direction, const int& count, std::array<int, 3>& pos) {
    if(direction == "forward") {
        pos[0] += count;
        pos[1] += count * pos[2];
    } else if(direction == "up") {
        pos[2] -= count;
    } else if(direction == "down") {
        pos[2] += count;
    }
}

int main() {
    std::ifstream inFile{"/home/tillb/Projects/advent-of-code/input/day02.input"};

    std::string direction{};
    int count{};

    std::array<int, 2> pos2d{};
    std::array<int, 3> pos3d{};

    while (inFile >> direction) {
        inFile >> count;
        updatePos(direction, count, pos2d);
        updatePos(direction, count, pos3d);
    }

    std::cout << "Horizontal Position: ( " << pos2d[0] << " | " << pos3d[0] << " )" << std::endl;
    std::cout << "Depth: ( " << pos2d[1] << " | "<< pos3d[1] << " )" << std::endl;
    std::cout << "Aim: ( - | " << pos3d[2] << " )" << std::endl;
    std::cout << "Product: ( " << pos2d[0] * pos2d[1] << " | "<< pos3d[0] * pos3d[1] << " )" << std::endl;

    return 0;
}
