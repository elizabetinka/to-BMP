#include "parsing.h"

void Parsing(int argc, char** argv, getInfo& arguments) {
    for (int i = 0; i < 6; i++) {
        arguments.flag[i] = false;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0 or strcmp(argv[i], "--lenght") == 0) {
            i++;
            arguments.length = static_cast<uint16_t>(atoi(argv[i]));
            arguments.flag[Length] = true;
        } else if (strcmp(argv[i], "-w") == 0 or strcmp(argv[i], "--width") == 0) {
            i++;
            arguments.width = static_cast<uint16_t>(atoi(argv[i]));
            arguments.flag[Width] = true;
        } else if (strcmp(argv[i], "-i") == 0 or strcmp(argv[i], "--input") == 0) {
            i++;
            arguments.input = argv[i];
            arguments.flag[Input] = true;
        } else if (strcmp(argv[i], "-o") == 0 or strcmp(argv[i], "--output") == 0) {
            i++;
            arguments.output = argv[i];
            arguments.flag[Output] = true;
        } else if (strcmp(argv[i], "-m") == 0 or strcmp(argv[i], "--max-iter") == 0) {
            i++;
            arguments.max_iter = atoi(argv[i]);
            arguments.flag[Max_iter] = true;
        } else if (strcmp(argv[i], "-f") == 0 or strcmp(argv[i], "--freq") == 0) {
            i++;
            arguments.freq = atoi(argv[i]);
            arguments.flag[Freq] = true;
        } else {
            std::cerr << "unknown option" << std::endl;
        }
    }
    // проверка на наличие обязательных параметров
    for (int i = 0; i < 4; i++) {
        if (!arguments.flag[i]) {
            std::cerr << "urequired parameters were not entered" << std::endl;
            exit(1);
        }
    }
}