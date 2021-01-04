//
// Created by Denis Ivanenko on 04.01.2021.
//
#include "pixel.h"

PIXELA getRed() {
	PIXELA red;
	red.A = 0xFF;
	red.B = 0;
	red.G = 0;
	red.R = 0xFF;

	return red;
}

PIXELA getBlue() {
	PIXELA blue;
	blue.A = 0xFF;
	blue.B = 0xFF;
	blue.G = 0;
	blue.R = 0;

	return blue;
}

PIXELA getGreen() {
	PIXELA green;
	green.A = 0xFF;
	green.B = 0;
	green.G = 0xFF;
	green.R = 0;

	return green;
}

PIXELA getYellow() {
	PIXELA yellow;
	yellow.A = 0xFF;
	yellow.B = 0;
	yellow.G = 0xFF;
	yellow.R = 0xFF;

	return yellow;
}

PIXELA getMagenta() {
	PIXELA magenta;
	magenta.A = 0xFF;
	magenta.B = 0xFF;
	magenta.G = 0;
	magenta.R = 0xFF;

	return magenta;
}

PIXELA getCyan() {
	PIXELA cyan;
	cyan.A = 0xFF;
	cyan.B = 0xFF;
	cyan.G = 0xFF;
	cyan.R = 0;

	return cyan;
}

PIXELA getWhite() {
	PIXELA white;
	white.A = 0xFF;
	white.B = 0xFF;
	white.G = 0xFF;
	white.R = 0xFF;

	return white;
}

PIXELA getBlack() {
	PIXELA black;
	black.A = 0xFF;
	black.B = 0;
	black.G = 0;
	black.R = 0;

	return black;
}

PIXELA getBrown() {
	PIXELA black;
	black.A = 0xFF;
	black.B = 0;
	black.G = 0x33;
	black.R = 0x66;

	return black;
}

PIXELA getOrange() {
	PIXELA black;
	black.A = 0xFF;
	black.B = 0;
	black.G = 0x99;
	black.R = 0xFF;

	return black;
}
