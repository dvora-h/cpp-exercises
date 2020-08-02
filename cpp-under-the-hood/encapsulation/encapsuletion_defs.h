/*
 Created by mby on 14/06/2020.
*/

#ifndef UTH_BOX_H
#define UTH_BOX_H

typedef struct Box{
    double length;
    double width;
    double height;
}Box;

void BOX_CONSRACTOR_D(Box* box, const double dim);
void BOX_CONSRACTOR_DDD(Box* box, const double l, const double w, const double h);
void BOX_DISTRACTOR(const Box*const box);
void BOX_print(const Box* const box);
Box* BOX_MULT_EQ_OPERATOR(Box* box, const double mult);


typedef struct Shelf{
    Box boxes[3];

}Shelf;
void SHELF_setBox(Shelf* shelf, const int index, const Box* const dims);
double SHELF_getVolume(const Shelf* const shelf);
void SHELF_print(const Shelf* const shelf);


#endif /*UTH_BOX_H*/
