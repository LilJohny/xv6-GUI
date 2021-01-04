#ifndef XV6_PIXEL
#define XV6_PIXEL

// Maximal and minimal RGBA channel values
#define COLOUR_MAX 255
#define COLOUR_MIN 0

// Structure representing a RGB 3-channeled pixel
typedef struct PIXEL {
    unsigned char B;
    unsigned char G;
    unsigned char R;
} PIXEL;

// Structure representing a RGB pixel with the 4th alpha channel for making the colour transparent/opaque
typedef struct PIXELA {
    unsigned char A;
    unsigned char B;
    unsigned char G;
    unsigned char R;
} PIXELA;


/*  Predefined colours  */


PIXELA getRed();

PIXELA getBlue();

PIXELA getGreen();

PIXELA getYellow();

PIXELA getMagenta();

PIXELA getCyan();

PIXELA getWhite();

PIXELA getBlack();

PIXELA getBrown();

PIXELA getOrange();


#endif