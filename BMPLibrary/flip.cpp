#define FLIP_H
#include "flip.h"

/**
* \brief функция, которая меняет местами два элемента типа unsigned char
* \param a первый элемент
* \param b второй элемент
* \author Воронков И.С.
* \date 13.01.2021
*/
void swap(unsigned char* a, unsigned char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void flip(bmpFile* inBmp, const char direction) {
	int height = inBmp->bmIHeader.Height;
	int width = inBmp->bmIHeader.Width;

	if (direction == 'H') {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width / 2; j++)
				swap(&inBmp->scan[i][j], &inBmp->scan[i][width-j-1]);
	}
	else if (direction == 'V') {
		for (int i = 0; i < height / 2; i++)
			for (int j = 0; j < width; j++)
				swap(&inBmp->scan[i][j], &inBmp->scan[height-i-1][j]);
	}
}
