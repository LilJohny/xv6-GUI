#include "window.h"
#include "user.h"
// add include with handlers

int onWindowClickHandler(WINDOW* window, int x, int y){
    for(int i = 0; i < window->num_regions; i++){
        if (window->regions[i].clickable == 1){
            // check if clicked on this particular region
            //fix
            if ((x > window->regions[i].x) && (x < (window->regions[i].x + window->regions[i].height))){
                if ((y > window->regions[i].y) && (y < (window->regions[i].y + window->regions[i].width))){
                    // check which handler to call
                    if(strcmp(window->regions[i].handler_string, "handler1") == 0){
                        printf(1, "Call handler1");
                    }

                    if(strcmp(window->regions[i].handler_string, "handler2") == 0){
                        printf(1, "Call handler2");
                    }
                }
            }
        }
    }

}