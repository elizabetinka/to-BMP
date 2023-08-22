#ifndef LABWORK_3_ELIZABETINKA_CREATE_BMP_H
#define LABWORK_3_ELIZABETINKA_CREATE_BMP_H

#include "parsing.h"

#include <iostream>
#include <cstring>
#include <deque>
#include <fstream>

std::string GetPath(const char* path);

// переводим число в представление little-endian, для этого переводим в систему счисления с осн 256
void ToNumbers4(int x,uint8_t numbers_4[]);

void CreateBmp(const char *path, const std::deque<std::deque<uint64_t>>& basic, const getInfo& arguments);

#endif //LABWORK_3_ELIZABETINKA_CREATE_BMP_H
