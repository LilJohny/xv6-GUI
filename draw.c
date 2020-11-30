/* --------------------------------------------------------------------------------------------------------------------- */
// Includes

#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "graphics_defs.h"
#include "font.h"

/* --------------------------------------------------------------------------------------------------------------------- */
// Pre-defined colors

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

/* --------------------------------------------------------------------------------------------------------------------- */
// PIXEL type casts

PIXEL PIXELAtoPIXEL(PIXELA pa) {
    PIXEL p;
    p.B = pa.B;
    p.G = pa.G;
    p.R = pa.R;

    return p;
}

PIXELA PIXELtoPIXELA(PIXEL p) {
    PIXELA pa;
    
    pa.A = 0xFF;
    pa.B = p.B;
    pa.G = p.G;
    pa.R = p.R;

    return pa;
}

/* --------------------------------------------------------------------------------------------------------------------- */
// Drawing functions

// Draws a single pixel with a given RGB colour
void drawPixel(int offset, PIXEL color_obj) {
    drawpixel(offset, color_obj.R, color_obj.G, color_obj.B);
}

// Draws a RGB pixel based on a RGBA pixel colour value
void drawPixelA(int offset, PIXELA color_obj) {
    float alpha;
    PIXEL* storeColor;

    if (color_obj.A == COLOUR_MAX) {
        drawpixel(offset, color_obj.R, color_obj.G, color_obj.B);
        return;
    }
    
    else if (color_obj.A == COLOUR_MIN) {
        return;
    }

    alpha = (float) color_obj.A / 255;

    getpixel(offset, storeColor);

    storeColor->R = storeColor->R * (1 - alpha) + color_obj.R * alpha;
    storeColor->G = storeColor->G * (1 - alpha) + color_obj.G * alpha;
    storeColor->B = storeColor->B * (1 - alpha) + color_obj.B * alpha;

    drawpixel(offset, storeColor->R, storeColor->G, storeColor->B);
}

// Draws a given character and returns its width (value to add to a pointer so the next char won't overlap this one)
int drawChar(char character, int x, int y, PIXELA color) {
    PIXEL* buf = display;
    int i, j;
    PIXEL *t;
    int ord = character - 0x20;
    if (ord < 0 || ord >= (CHAR_NUM - 1)) {
        return -1;
    }
    for (i = 0; i < CHAR_HEIGHT; i++) {
        for (j = 0; j < CHAR_WIDTH; j++) {
            if (Font_Default[ord][i][j] == 1) {
                t = buf + (y + i) * DISPLAY_WIDTH + x + j;
                //drawPixelA(t, color);
                drawPixel(t-display, PIXELAtoPIXEL(color));
            }
        }
    }
    return CHAR_WIDTH;
}

// Draws a sequence of characters
void drawStr(char *str, int x, int y, PIXELA color) {
    int offset_x = 0;

    while (*str != '\0') {
        offset_x += drawChar(*str, x + offset_x, y, color);
        str++;
    }
}

/* --------------------------------------------------------------------------------------------------------------------- */
// Demo function of GUI capabilities

void demo() {

    //PIXEL *pix2 = display;

    int offset = 0;

    const char* words[10];
    words[0] = "Red";
    words[1] = "Blue";
    words[2] = "Green";
    words[3] = "Yellow";
    words[4] = "Cyan";
    words[5] = "Magenta";
    words[6] = "White";
    words[7] = "Black";
    words[8] = "Orange";
    words[9] = "Brown";

    PIXELA colours[10];
    colours[0] = getRed();
    colours[1] = getBlue();
    colours[2] = getGreen();
    colours[3] = getYellow();
    colours[4] = getCyan();
    colours[5] = getMagenta();
    colours[6] = getWhite();
    colours[7] = getBlack();
    colours[8] = getOrange();
    colours[9] = getBrown();

    offset = 0;
    int offsetY = 0;
    for (int idx=0; idx < 10; idx++) {

        int wordLen = strlen(words[idx]);

        for (int q=0; q<wordLen; q++) {
            offset += drawChar(words[idx][q], 50+offset, 80+offsetY, colours[idx]);
        }
        offset = 0;
        offsetY += 15;
    }
}

int main(void) {
  printf(1, "\nshell display address: 0x%x\n\n", display);
  
  demo();

  PIXELA color;
  color.A = 0x7F;
  color.R = 0xFF;
  color.G = 0x00;
  color.B = 0x00;
  drawPixelA(5000, color);
  drawPixelA(5001, color);
  drawPixelA(5002, color);
  drawStr("Hello World!", 50, 400, color);

  while(1) {
      // Busy loop
  }
  exit();
}