#include "bright.h"

void bright(bmpFile* inBmp, short f) {
	int height = inBmp->bmIHeader.Height;
	int width = inBmp->bmIHeader.Width;

	if (f > 0) {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				inBmp->scan[i][j] <<= f;
	}
	else if (f < 0) {
		f = -f;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				inBmp->scan[i][j] >>= f;
	}
}