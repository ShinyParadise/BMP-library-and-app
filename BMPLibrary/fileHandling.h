#include "structs.h"

#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>


/**
* \brief функция чтения bmp-файла
* \details читаемый файл имеет вид "input01.bmp", где 01 - его номер
* \param num номер файла
* \author Воронков И.С.
* \date 13.01.2021
*/
bmpFile readBMP(int num);

/**
* \brief функция записи bmp-файла
* \details записываем файл имеет вид "output01.bmp", где 01 - его номер
* \param num номер файла
* \param inBmp bmp-структура для записи
* \author Воронков И.С.
* \date 13.01.2021
*/
void writeBMP(int num, bmpFile* inBmp);
