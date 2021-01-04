#ifndef XV6_GUI_BITMAP_H
#define XV6_GUI_BITMAP_H

#endif //XV6_GUI_BITMAP_H

#include "user.h"

typedef struct BMP_HEADER {
	ushort bfType;
	uint bfSize;
	ushort bfReserved1;
	ushort bfReserved2;
	uint btOffBits;
} __attribute__((packed)) BMP_HEADER;

typedef struct BMP_INFO_HEADER {
	uint biSize;
	int biWidth;
	int biHeight;
	ushort biPlanes;
	ushort biBitCount;
	uint biCompression;
	uint biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	uint biCirUserd;
	uint biCirImportant;
} __attribute__((packed)) BMP_INFO_HEADER;

