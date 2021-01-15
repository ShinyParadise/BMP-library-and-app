#include "structs.h"

/**
* \brief функция увеличения разрешения картинки
* \details повышает значения высоты в V раз и ширины в H раз
* \param inBmp входная bmp-структура
* \param V коэффициент увеличения высоты изображения
* \param H коэффициент увеличения ширины изображения
* \author Воронков И.С.
* \date 13.01.2021
*/
void upscale(bmpFile* inBmp, short V, short H);