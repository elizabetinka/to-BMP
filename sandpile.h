#ifndef LABWORK_3_ELIZABETINKA_SANDPILE_H
#define LABWORK_3_ELIZABETINKA_SANDPILE_H

#include "parsing.h"

#include <deque>
#include <fstream>
#include <set>

enum KeysOfAdd {
    up = 0, left = 1, down = 2, right = 3
};

// считываем данные из tsv файла
void ReadingInput(const char* path, std::deque<std::deque<uint64_t>>& basic, const getInfo& arguments,
                  int &count_cells_more4);

void AddPlace(std::deque<std::deque<uint64_t>>& basic, getInfo& arguments, KeysOfAdd key);

void Iteration(std::deque<std::deque<uint64_t>>& basic, getInfo& arguments, int& count_cells_more4);

#endif //LABWORK_3_ELIZABETINKA_SANDPILE_H
