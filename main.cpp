#include "create_bmp.h"
#include "parsing.h"
#include "sandpile.h"

#include <deque>
#include <cstdlib>

int main(int argc, char** argv) {
    getInfo arguments;
    Parsing(argc, argv, arguments);
    std::deque<std::deque<uint64_t>> basic;
    // задаем размер
    basic.resize(arguments.width);
    for (int i = 0; i < arguments.width; i++) {
        basic[i].resize(arguments.length, 0);
    }
    // хранит в себе количество ячеек >=4 на данный момент
    int count_cells_more4 = 0;
    ReadingInput(arguments.input, basic, arguments, count_cells_more4);
    int now_iterations = 0;
    while (count_cells_more4 != 0) {
        Iteration(basic, arguments, count_cells_more4);
        now_iterations++;
        if (arguments.flag[Freq] == true) {
            if (arguments.freq != 0) {
                if (now_iterations % arguments.freq == 0 && count_cells_more4 != 0) {
                    CreateBmp(arguments.output, basic, arguments);
                }
            }
        }
        if (arguments.flag[Max_iter] == true) {
            if (now_iterations == arguments.max_iter) {
                break;
            }
        }
    }
    CreateBmp(arguments.output, basic, arguments);

    return 0;
}
