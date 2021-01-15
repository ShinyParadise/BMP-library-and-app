#include "rotate.h"

#ifndef FLIP_H
#define FLIP_H
#include "flip.h"
#endif

void rotate(bmpFile* inBmp, short angle) {
	int height = inBmp->bmIHeader.Height;
	int width = inBmp->bmIHeader.Width;
	unsigned char** rotatedImg;
	int newH, newW, RowSize;
	short padding;

	switch (angle) {
		case 180:
			flip(inBmp, 'H');
			flip(inBmp, 'V');
			break;
		case 90:
			padding = 4 - height % 4;
			RowSize = height;
			if (height % 4 != 0) {
				RowSize += padding;
			}

			rotatedImg = new unsigned char* [width];
			for (int i = 0; i < width; i++)
				rotatedImg[i] = new unsigned char[RowSize]();

			for (int i = 0; i < width; i++)
				for (int j = 0; j < height; j++)
					rotatedImg[i][j] = inBmp->scan[height-j-1][i];

			newW = RowSize;
			newH = width;
			inBmp->bmIHeader.Height = newH;
			inBmp->bmIHeader.Width = height;

			for(int i = 0; i<height; i++)
				delete[] inBmp->scan[i];
			delete[] inBmp->scan;
			inBmp->scan = new unsigned char* [newH];
			for (int i = 0; i < newH; i++)
				inBmp->scan[i] = new unsigned char[newW]();
			

			for (int i = 0; i < newH; i++)
				for (int j = 0; j < newW; j++)
					inBmp->scan[i][j] = rotatedImg[newH-i-1][newW-j-1];

			for (int i = 0; i < newH; i++)
				delete[] rotatedImg[i];
			delete[] rotatedImg;
			
			break;
		case 270:
			padding = 4 - height % 4;
			RowSize = height;
			if (height % 4 != 0) {
				RowSize += padding;
			}

			rotatedImg = new unsigned char* [width];
			for (int i = 0; i < width; i++)
				rotatedImg[i] = new unsigned char[RowSize]();

			for (int i = 0; i < width; i++)
				for (int j = 0; j < height; j++)
					rotatedImg[i][j] = inBmp->scan[height-j-1][i];

			inBmp->bmIHeader.Height = width;
			inBmp->bmIHeader.Width = height;

			for (int i = 0; i < height; i++)
				delete[] inBmp->scan[i];
			delete[] inBmp->scan;

			inBmp->scan = rotatedImg;
			break;
		default:
			break;
	}
}
