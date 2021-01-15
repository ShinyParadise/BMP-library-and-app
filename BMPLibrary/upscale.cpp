#define imgMaxH 1000 ///< максимально возможная высота изображения
#define imgMaxW 1000 ///< максимально возможная ширина изображения
#include "upscale.h"

#pragma once
#include <iostream>
using namespace std;

void upscale(bmpFile* inBmp, short V, short H) {
	try {
		if (H*inBmp->bmIHeader.Width > imgMaxW || V*inBmp->bmIHeader.Height > imgMaxH)
			throw "Output image is too big.";

		int oldW = inBmp->bmIHeader.Width;
		int oldH = inBmp->bmIHeader.Height;

		int scaledW = inBmp->bmIHeader.Width * H;
		int scaledH = inBmp->bmIHeader.Height * V;
		unsigned int diff = scaledW*scaledH - oldH*oldW;

		inBmp->bmIHeader.Width = scaledW;
		inBmp->bmIHeader.Height = scaledH;
		inBmp->bmFHeader.bfSize += diff;
		inBmp->bmIHeader.SizeImage *= V * H;

		short padding = 4 - scaledW % 4;
		int RowSize = scaledW;
		if (scaledW % 4 != 0) {
			RowSize += padding;
		}

		auto scaledImg = new unsigned char* [scaledH];
		for (int i = 0; i < scaledH; i++)
			scaledImg[i] = new unsigned char[RowSize]();

		int szCopyV = scaledH / oldH;
		int szCopyH = scaledW / oldW;

		for (int row = 0; row < scaledH; row++)
			for (int col = 0; col < scaledW; col++)
				scaledImg[row][col] = inBmp->scan[row / szCopyV][col / szCopyH];


		for (int i = 0; i < oldH; i++)
			delete[] inBmp->scan[i];
		delete[] inBmp->scan;
		inBmp->scan = scaledImg;

	}
	catch (const char* e) {
		cerr << "Error: " << e << endl;
	}
}