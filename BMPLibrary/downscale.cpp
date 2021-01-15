#pragma once
#include "downscale.h"
#include <iostream>
using namespace std;

void downscale(bmpFile* inBmp, short V, short H) {
	try {
		if (inBmp->bmIHeader.Width % H != 0 || inBmp->bmIHeader.Height % V != 0)
			throw "Image is unscaleable.";

		int oldW = inBmp->bmIHeader.Width;
		int oldH = inBmp->bmIHeader.Height;

		int scaledH = inBmp->bmIHeader.Height / V;
		int scaledW = inBmp->bmIHeader.Width / H;
		unsigned int diff = oldH*oldW - scaledH*scaledW;

		inBmp->bmIHeader.Width /= H;
		inBmp->bmIHeader.Height /= V;
		inBmp->bmFHeader.bfSize -= diff;
		inBmp->bmIHeader.SizeImage /= V * H;

		short padding = 4 - scaledW % 4;
		int RowSize = scaledW;
		if (scaledW % 4 != 0) {
			RowSize += padding;
		}

		auto scaledImg = new unsigned char* [scaledH];
		for (int i = 0; i < scaledH; i++)
			scaledImg[i] = new unsigned char[RowSize]();

		for (int row = 0; row < oldH; row++)
			for (int col = 0; col < oldW; col++)
				if (row % V == 0 && col % H == 0)
					scaledImg[row / V][col / H] = inBmp->scan[row][col];

		for (int i = 0; i < oldH; i++)
			delete[] inBmp->scan[i];
		delete[] inBmp->scan;

		inBmp->scan = scaledImg;
	}
	catch (const char* e) {
		cerr << "Error: " << e << endl;
	}
}
