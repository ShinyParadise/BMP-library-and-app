#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cassert>
#include "fileHandling.h"

bmpFile readBMP(int num) {
    bmpFile input;

    char infile[20] = { 0 };
    sprintf(infile, "input%02d.bmp", num);
    FILE* fin = fopen(infile, "rb");

    fread(&input.bmFHeader, sizeof(bmfh), 1, fin);
    fread(&input.bmIHeader, sizeof(bmih), 1, fin);
    fread(&input.palette, sizeof(input.palette), 1, fin);

    int width = input.bmIHeader.Width;
    int height = input.bmIHeader.Height;

    short int padding = 4 - width % 4;
    int RowSize = width;
    if (width % 4 != 0) {
        RowSize += padding;
    }

    input.scan = new unsigned char* [height]; // кол-во строк в растровой развертке (высота изобр)
    for (int i = 0; i < height; i++)
        input.scan[i] = new unsigned char[RowSize](); // кол-во столбцов в растровой развертке \
                                                      (ширина изобр)

    for (int i = 0; i < height; i++)
        for (int j = 0; j < RowSize; j++)
            fread(&input.scan[i][j], sizeof(char), 1, fin);
    
    
    fclose(fin);
    return input;
}

void writeBMP(int num, bmpFile* inBmp) {
    char outfile[20] = { 0 };
    sprintf(outfile, "output%02d.bmp", num);
    FILE* fout = fopen(outfile, "wb");

    fwrite(&inBmp->bmFHeader, sizeof(bmfh), 1, fout);
    fwrite(&inBmp->bmIHeader, sizeof(bmih), 1, fout);
    fwrite(&inBmp->palette, sizeof(inBmp->palette), 1, fout);

    int height = inBmp->bmIHeader.Height;
    int width = inBmp->bmIHeader.Width;
    short int padding = 4 - width % 4;
    int RowSize = width;
    if (width % 4 != 0) {
        RowSize += padding;
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < RowSize; j++)
            fwrite(&inBmp->scan[i][j], sizeof(char), 1, fout);

    for (int i = 0; i < height; i++)
        delete[] inBmp->scan[i];
    delete[] inBmp->scan;

    fclose(fout);
}
