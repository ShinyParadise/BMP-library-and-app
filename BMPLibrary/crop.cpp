#include "crop.h"

void crop(int delta, bmpFile* inBmp) {
	int height = inBmp->bmIHeader.Height;
	int width = inBmp->bmIHeader.Width;
	int deltaH = height - delta * 2;
	int deltaW = width - delta * 2;

	int oldSize = width * height;
	int newSize = deltaH * deltaW;
	inBmp->bmIHeader.Height -= delta * 2;
	inBmp->bmIHeader.Width -= delta * 2;
	inBmp->bmFHeader.bfSize -= oldSize - newSize;
	inBmp->bmIHeader.SizeImage = newSize;

	short padding = 4 - deltaW % 4;
	int RowSize = deltaW;
	if (deltaW % 4 != 0) {
		RowSize += padding;
	}

	auto centerImg = new unsigned char* [deltaH];
	for (int i = 0; i < deltaH; i++)
		centerImg[i] = new unsigned char[RowSize]();

	for (int row = 0, i = delta; i < height-delta; row++, i++)
		for (int col = 0, j = delta; j < width-delta; col++, j++)
			centerImg[row][col] = inBmp->scan[i][j];

	for (int i = 0; i < height; i++)
		delete[] inBmp->scan[i];
	delete[] inBmp->scan;

	inBmp->scan = centerImg;
}