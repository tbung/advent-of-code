#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::ifstream inFile{"/home/tillb/Projects/aoc21/input/day01.input"};

    std::vector<int> window{};
    int current{};
    int count{};
    int winCount{};

    for (int i{}; i < 4; i++) {
        inFile >> current;

        if((window.size() > 0) && (current > window.back()))
            count++;

        window.push_back(current);
    }

    while (inFile >> current) {
        window.erase(window.begin());

        if(current > window.back())
            count++;

        window.push_back(current);

        if ((window[1] + window[2] + window[3]) >
            (window[0] + window[1] + window[2]))
            winCount++;
    }

    std::cout << "Count: " << count << std::endl;
    std::cout << "Moving Count: " << winCount << std::endl;

    return 0;
}
