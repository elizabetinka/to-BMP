#include "sandpile.h"

void ReadingInput(const char* path, std::deque<std::deque<uint64_t>>& basic, const getInfo& arguments,
                  int& count_cells_more4) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла " << path << std::endl;
        exit(1);
    }
    uint16_t i=0;
    uint16_t j=0;
    uint64_t pixels;
    while (fin.good()) {
        fin >> i;
        fin >> j;
        fin >> pixels;
        basic[i][j] = pixels;
        if (pixels >= 4) {
            count_cells_more4++;
        }
    }
}

void AddPlace(std::deque<std::deque<uint64_t>>& basic, getInfo& arguments, KeysOfAdd key) {
    std::deque<uint64_t> a;
    switch (key) {
        case up:
            a.resize(arguments.length, 0);
            basic.push_front(a);
            arguments.width++;
            break;
        case down:
            a.resize(arguments.length, 0);
            basic.push_back(a);
            arguments.width++;
            break;
        case left:
            for (uint16_t i = 0; i < arguments.width; i++) {
                basic[i].push_front(0);
            }
            arguments.length++;
            break;
        case right:
            for (uint16_t i = 0; i < arguments.width; i++) {
                basic[i].push_back(0);
            }
            arguments.length++;
            break;
    }
}

void Iteration(std::deque<std::deque<uint64_t>>& basic, getInfo& arguments, int& count_cells_more4) {
    // хранит в себе индексы, до которых мы еще не дошли, но мы их уже сделали >=4
    std::set<std::pair<uint16_t, uint16_t>> ignoring;
    std::pair<uint16_t, uint16_t> temporary;
    for (uint16_t i = 0; i < arguments.width; i++) {
        for (uint16_t j = 0; j < arguments.length; j++) {
            temporary = std::make_pair(i, j);
            if (ignoring.count(temporary) == 1) {
                continue;
            }
            if (basic[i][j] >= 4) {
                if (i == 0) {
                    AddPlace(basic, arguments, up);
                    i++;
                }
                if (j == 0) {
                    AddPlace(basic, arguments, left);
                    j++;
                }
                if (i == arguments.width - 1) {
                    AddPlace(basic, arguments, down);
                }
                if (j == arguments.length - 1) {
                    AddPlace(basic, arguments, right);
                }

                basic[i][j] = basic[i][j] - 4;
                basic[i - 1][j]++;
                basic[i][j - 1]++;
                basic[i + 1][j]++;
                basic[i][j + 1]++;

                if (basic[i + 1][j] == 4) {
                    temporary = std::make_pair(i + 1, j);
                    ignoring.insert(temporary);
                    count_cells_more4++;
                }

                if (basic[i][j + 1] == 4) {
                    temporary = std::make_pair(i, j + 1);
                    ignoring.insert(temporary);
                    count_cells_more4++;
                }

                if (basic[i][j] < 4) {
                    count_cells_more4--;
                }
                if (basic[i - 1][j] == 4) {
                    count_cells_more4++;
                }
                if (basic[i][j - 1] == 4) {
                    count_cells_more4++;
                }
            }
        }
    }
}
