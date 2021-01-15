#ifndef STRUCTS_H
#define STRUCTS_H

#pragma pack (push, 2)
typedef struct bmfileheader {
    char bfType[2]; ///< Сигнатура bmp-файла (="BM")
    unsigned int bfSize; ///< Размер всего bmp-файла в байтах
    short int Reserved1; ///< Зарезервированное поле (=0)
    short int Reserved2; ///< Зарезервированное поле (=0)
    unsigned int OffBits; ///< Смещение (в байтах) массива пикселов от начала файла
} bmfh;
#pragma pack(pop)

typedef struct bminfoheader {
    unsigned int biSize; ///< Размер структуры BITMAPINFOHEADER в байтах
    int Width; ///< Ширина картинки в пикселах
    int Height; ///< Высота картинки в пикселах
    short int Planes; ///< Количество цветовых плоскостей
    short int BitCount; ///< Количество битов на 1 пиксел
    int Compression;
    unsigned int SizeImage; ///< Размер массива пикселов в байтах
    int XPelsPerMeter;
    int YPelsPerMeter;
    int ClrUsed;
    int ClrImportant;
} bmih;

typedef struct rgbquad {
    char rgbBlue;
    char rgbGreen;
    char rgbRed;
    char rgbReserved;
} rgbq;

typedef struct bmp {
    bmfh bmFHeader; ///< Cтруктура заголовка bmp-файла
    bmih bmIHeader; ///< Структура описания формата изображения
    rgbq palette[256]; ///< Палитра
    unsigned char** scan; ///< Растровая развертка изображения
} bmpFile;
#endif
