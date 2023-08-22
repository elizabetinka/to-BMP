#ifndef LABWORK_3_ELIZABETINKA_PARSING_H
#define LABWORK_3_ELIZABETINKA_PARSING_H

#include <iostream>
#include <cstring>
#include <fstream>


enum Options {
    Length = 0, Width = 1, Input = 2, Output = 3, Max_iter = 4, Freq = 5
};

struct getInfo {
    uint16_t length;
    uint16_t width;
    char* input;
    char* output;
    size_t max_iter;
    size_t freq;
    // проверяет, какие введены параметры (True-вводились, False-нет)
    bool flag[6];
};

void Parsing(int argc, char** argv, getInfo& arguments);

#endif //LABWORK_3_ELIZABETINKA_PARSING_H
