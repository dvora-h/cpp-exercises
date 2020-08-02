/*
 Created by mby on 14/06/2020.
*/
#include "box.h"
#include <stdio.h>
const char* message = "The total volume held on the shelf is";
void BOX_CONSRACTOR_D(Box* box, const double dim){
    box->length = dim;
    box->height = dim;
    box->width = dim;
    BOX_print(box);
}
void BOX_CONSRACTOR_DDD(Box* box, const double l, const double w, const double h){
    box->length = l;
    box->height = h;
    box->width = w;
    BOX_print(box);
}
void BOX_DISTRACTOR(const Box* const box){
    printf("Box destructor, %f x %f x %f\n", box->width, box->height, box->length);
}
void BOX_print(const Box* const box){
    printf("Box: %f x %f x %f\n", box->length, box->width, box->height);
}

Box* BOX_MULT_EQ_OPERATOR(Box* box, const double mult){
    box->width *= mult;
    box->height *= mult;
    box->length *= mult;
    return box;
}


void SHELF_setBox(Shelf* shelf, const int index, const Box* const dims){
    shelf->boxes[index] = *dims;
}
double SHELF_getVolume(const Shelf* shelf){
    size_t i;
    double vol = 0;
    for (i = 0; i < 3; ++i)
        vol += shelf->boxes[i].height * shelf->boxes[i].length * shelf->boxes[i].width;
    return vol;
}

void SHELF_print(const Shelf* const shelf){
    printf("%s %f\n", message, SHELF_getVolume(shelf));
}
