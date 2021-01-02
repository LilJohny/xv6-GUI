#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "graphics_defs.h"
#include "pixel.h"
#include "bitmap.h"

void readBMPHeader(int bmpFile, BMP_HEADER *bmpFileHeader, BMP_INFO_HEADER *bmpInfoHeader) {
    read(bmpFile, bmpFileHeader, sizeof(BMP_HEADER));
    read(bmpFile, bmpInfoHeader, sizeof(BMP_INFO_HEADER));
}

int readBitmapFile(char *fileName, PIXELA *result, int *height, int *width) {
    int i;
    int bmpFile = open(fileName, 0);
    if (bmpFile < 0) {
        return -1;
    }

    BMP_HEADER bmpFileHeader;
    BMP_INFO_HEADER bmpInfoHeader;

    readBMPHeader(bmpFile, &bmpFileHeader, &bmpInfoHeader);
    *width = bmpInfoHeader.biWidth;
    *height = bmpInfoHeader.biHeight;
    int column = bmpInfoHeader.biWidth;
    int row = bmpInfoHeader.biHeight;
    int bits = bmpInfoHeader.biBitCount;
    char tmpBytes[3];
    int rowBytes = column * bits / 8;
    char *buf = (char *) result;
    for (i = 0; i < row; i++) {
        if (bits == 32) {
            read(bmpFile, buf + i * rowBytes, rowBytes);
        } else {
            int j = 0;
            for (j = 0; j < column; j++) {
                read(bmpFile, buf + i * column * 4 + j * sizeof(PIXELA), 3);
                *(buf + i * column * 4 + j * sizeof(PIXELA) + 3) = 255;
            }
        }
        if (rowBytes % 4 > 0) {
            read(bmpFile, tmpBytes, 4 - (rowBytes % 4));
        }
    }

    close(bmpFile);
    return 0;
}

int readBMP(char *fileName, struct PIXEL *result, int *height, int *width) {
    int i;
    int bmpFile = open(fileName, 0);
    if (bmpFile < 0) {
        return -1;
    }

    BMP_HEADER bmpFileHeader;
    BMP_INFO_HEADER bmpInfoHeader;

    readBMPHeader(bmpFile, &bmpFileHeader, &bmpInfoHeader);
    *width = bmpInfoHeader.biWidth;
    *height = bmpInfoHeader.biHeight;
    int column = bmpInfoHeader.biWidth;
    int row = bmpInfoHeader.biHeight;
    int bits = bmpInfoHeader.biBitCount;
    char tmpBytes[3];
    int rowBytes = column * 3;
    char *buf = (char *) result;
    for (i = 0; i < row; i++) {
        if (bits == 24) {
            read(bmpFile, buf + i * rowBytes, rowBytes);
        } else {
            int j = 0;
            for (j = 0; j < column; j++) {
                read(bmpFile, buf + i * column * 3 + j * sizeof(PIXEL), 3);
                read(bmpFile, tmpBytes, 1);
            }
        }

        if (rowBytes % 4 > 0) {
            read(bmpFile, tmpBytes, 4 - (rowBytes % 4));
        }
    }

    close(bmpFile);
    return 0;
}

