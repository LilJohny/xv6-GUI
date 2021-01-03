	int width;
#ifndef XV6_GUI_WINDOW_H
#define XV6_GUI_WINDOW_H

#endif //XV6_GUI_WINDOW_H

#define IMAGE_REGION 0
#define TEXT_REGION 0

typedef struct WINDOW_REGION {
    unsigned int region_type;
    // x and y starting from 0,0 of the parent window
    unsigned int x;
    unsigned int y;
    unsigned int height;
    unsigned int width;
    int clickable;//1 if clickable
    // string corresponding to a function-handler for this region (if clickable)
    char* handler_string;
    // set icon if region_type = IMAGE_REGION, set text if region_type = TEXT_REGION
    ICON* icon;
    char* text;
} WINDOW_REGION;

typedef struct WINDOW {
    // x and y starting from 0,0 of the display
    WINDOW_REGION* regions;
    unsigned int num_regions;
    unsigned int x;
    unsigned int y;
} WINDOW;


