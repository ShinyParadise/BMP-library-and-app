#include "structs.h"

/**
* \brief функция уменьшения разрешения картинки
* \details изменяет значения высоты в V раз и ширины в H раз
* \param inBmp входная bmp-структура
* \param V коэффициент уменьшения высоты изображения
* \param H коэффициент уменьшения ширины изображения
* \author Воронков И.С.
* \date 13.01.2021
*/
void downscale(bmpFile* inBmp, short V, short H);