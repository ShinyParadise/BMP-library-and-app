#include "structs.h"

/**
* \brief функция изменения яркости картинки
* \details изменяет значения цветовой компоненты путем сдвига на f битов
* \param inBmp - входная bmp-структура
* \param f - число сдвига яркости (f<0 - уменьшение, f>0 - увеличение)
* \author Воронков И.С.
* \date 13.01.2021
*/
void bright(bmpFile* inBmp, short f);