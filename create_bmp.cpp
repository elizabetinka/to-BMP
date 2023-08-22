#include "create_bmp.h"
#include "parsing.h"

std::string GetPath(const char* path) {
    static int count_picture = 0;
    count_picture++;
    return static_cast<std::string>(path) + "/my_bmp" + std::to_string(count_picture) + ".bmp";
}

void ToNumbers4(int x, uint8_t numbers_4[]) {
    numbers_4[3] = static_cast<uint8_t>(x / (256 * 256 * 256));
    x = x % (256 * 256 * 256);
    numbers_4[2] = static_cast<uint8_t>(x / (256 * 256));
    x = x % (256 * 256);
    numbers_4[1] = static_cast<uint8_t>(x / (256));
    x = x % (256);
    numbers_4[0] = static_cast<uint8_t>(x);
}

void CreateBmp(const char* path, const std::deque<std::deque<uint64_t>>& basic, const getInfo& arguments) {
    std::ofstream fout;
    fout.open(GetPath(path), std::ios::binary);
    //std::cout<<GetPath(path);
    if (!fout.is_open()) {
        std::cerr << " Файл не создан";
        exit(1);
    }
    // делаем длину в байтах кратной 4 (так как занимаемое кол-во байт length/2)
    uint16_t length = arguments.length;
    if (length % 8 != 0) {
        length = length + 8 - length % 8;
    }

    // массивы для хранения отдельных байтов числа
    uint8_t numbers_4[4];
    uint8_t numbers_2[2];
    // временная переменная для вычислений с числами размером 32 бит
    int32_t number_4_sigh;

    const int kBitmapFileHeder = 14;
    const int kBitmapInfo = 40;
    const int kTableOfColors = 20;
    const int kbiBitCount = 4;
    const int kCountOfColors = 5;

    // BITMAPFILEHEADER
    // bfType
    numbers_2[0] = 0x4D;
    numbers_2[1] = 0x42; // BM
    fout << numbers_2[1] << numbers_2[0];

    // bfSize
    int64_t bfSize = kBitmapFileHeder + kBitmapInfo + kTableOfColors + (length * arguments.width) / 2;
    ToNumbers4(bfSize, numbers_4);
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // bfReserved1
    numbers_2[0] = 0;
    numbers_2[1] = 0;
    fout << numbers_2[0] << numbers_2[1];

    // bfReserved2
    fout << numbers_2[0] << numbers_2[1];

    // bfOffBits
    numbers_4[0] = static_cast<uint8_t>(kBitmapFileHeder + kBitmapInfo + kTableOfColors); // = 74
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // BITMAPINFO
    // biSize
    numbers_4[0] = static_cast<uint8_t>(kBitmapInfo); // = 40
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biWidth
    number_4_sigh = arguments.length;
    ToNumbers4(number_4_sigh, numbers_4);
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biHeight
    number_4_sigh = arguments.width;
    ToNumbers4(number_4_sigh, numbers_4);
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biPlanes
    numbers_2[0] = 1;
    numbers_2[1] = 0;
    fout << numbers_2[0] << numbers_2[1];

    // biBitCount
    numbers_2[0] = static_cast<uint8_t>(kbiBitCount); // = 4
    numbers_2[1] = 0;
    fout << numbers_2[0] << numbers_2[1];

    // biCompression
    numbers_4[0] = 0;
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biSizeImage
    numbers_4[0] = 0;
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biXPelsPerMeter
    numbers_4[0] = 0;
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biYPelsPerMeter
    numbers_4[0] = 0;
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biClrUsed
    numbers_4[0] = static_cast<uint8_t>(kCountOfColors); // = 5
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // biClrImportant
    numbers_4[0] = static_cast<uint8_t>(kCountOfColors); // = 5
    numbers_4[1] = 0;
    numbers_4[2] = 0;
    numbers_4[3] = 0;
    fout << numbers_4[0] << numbers_4[1] << numbers_4[2] << numbers_4[3];

    // RGBQUAD
    uint8_t col[4] = {255, 255, 255, 0}; // white
    fout << col[2] << col[1] << col[0] << col[3];

    col[0] = 0;
    col[1] = 255;
    col[2] = 0; // lime
    fout << col[2] << col[1] << col[0] << col[3];

    col[0] = 138;
    col[1] = 43;
    col[2] = 226; // blue violet
    fout << col[2] << col[1] << col[0] << col[3];

    col[0] = 255;
    col[1] = 255;
    col[2] = 0; // yellow
    fout << col[2] << col[1] << col[0] << col[3];

    col[0] = 0;
    col[1] = 0;
    col[2] = 0; // black
    fout << col[2] << col[1] << col[0] << col[3];

    // переменная, содержащая в себе байт, который нужно записать в файл
    uint8_t q;

    // отдельные переменные для обращения по элементу basic, чтобы не выйти за его границу
    uint8_t a;
    uint8_t b;

    // вносим информацию о данных растрового массива
    for (int i = arguments.width - 1; i >= 0; i--) {
        for (uint16_t j = 0; j < length; j = j + 2) {
            if (j >= arguments.length) {
                a = 0;
                b = 0;
            } else if ((j + 1 >= arguments.length)) {
                if (basic[i][j] > 4) {
                    a = 4;
                } else {
                    a = basic[i][j];
                }
                b = 0;
            } else {
                if (basic[i][j] > 4) {
                    a = 4;
                } else {
                    a = basic[i][j];
                }
                if (basic[i][j + 1] > 4) {
                    b = 4;
                } else {
                    b = basic[i][j + 1];
                }
            }
            q = (a << 4) + b;
            fout << q;
        }
    }
    fout.close();
}