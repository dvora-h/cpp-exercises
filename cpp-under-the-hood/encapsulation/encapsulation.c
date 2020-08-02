#include <stdio.h>
#include "box.h"
#include "inheritance_defs.h"
static Box largeBox;
static Box box99;
static Box box88;
//extern const char* const DEF_MSG;
extern const char* message;
extern const char* const names[];
void doBoxes(){
    printf("\n--- Start doBoxes() ---\n\n");
    Box b1;
    BOX_CONSRACTOR_D(&b1, 3);
    Box b2;
    BOX_CONSRACTOR_DDD(&b2, 4, 5, 6);
    printf("b1 volume: %f\n",b1.height * b1.length * b1.width);
    printf("b2 volume: %f\n", b2.height * b2.length * b2.width);
    BOX_MULT_EQ_OPERATOR(&b1, 1.5);
    BOX_MULT_EQ_OPERATOR(&b2, 0.5);
    printf("b1 volume: %f\n", b1.height * b1.length * b1.width);
    printf("b2 volume: %f\n", b2.height * b2.length * b2.width);
    Box b3 = b2;
    Box ret = b2;
    BOX_MULT_EQ_OPERATOR(&ret, 3);
    Box b4 = ret;
    printf("b3 %s b4\n", b3.width == b4.width && b3.height == b4.height && b3.length == b4.length ? "equals" : "does not equal");
    BOX_MULT_EQ_OPERATOR(&b3, 1.5);
    BOX_MULT_EQ_OPERATOR(&b4, 0.5);
    printf("Now, b3 %s b4\n", b3.width == b4.width && b3.height == b4.height && b3.length == b4.length ? "equals" : "does not equal");
    printf("\n--- End doBoxes() ---\n\n");
    BOX_DISTRACTOR(&b1);
    BOX_DISTRACTOR(&b2);
    BOX_DISTRACTOR(&b3);
    BOX_DISTRACTOR(&b4);
}

void thisFunc()
{
    printf("\n--- thisFunc() ---\n\n");
    if (box99.height == 0){
        BOX_CONSRACTOR_DDD(&box99, 99, 99, 99);
    }
    BOX_MULT_EQ_OPERATOR(&box99, 10);
}
void thatFunc()
{
    printf("\n--- thatFunc() ---\n\n");
    if (box88.height == 0){
        BOX_CONSRACTOR_DDD(&box88, 88, 88, 88);
    }
    BOX_MULT_EQ_OPERATOR(&box88, 10);
}
void doShelves(){
    printf("\n--- start doShelves() ---\n\n");
    Box aBox;
    BOX_CONSRACTOR_D(&aBox, 5);
    Shelf aShelf;
    for(int i = 0; i<3; i++){
        BOX_CONSRACTOR_D(&(aShelf.boxes[i]), 1);
    }
    SHELF_print(&aShelf);
    SHELF_setBox(&aShelf, 1, &largeBox);
    SHELF_setBox(&aShelf, 0, &aBox);
    message = "This is the total volume on the shelf:";
    SHELF_print(&aShelf);
    message = "Shelf's volume:";
    SHELF_print(&aShelf);
    Box temp;
    BOX_CONSRACTOR_DDD(&temp, 2, 4, 6);
    SHELF_setBox(&aShelf, 1, &temp);
    BOX_DISTRACTOR(&temp);
    Box temp2;
    BOX_CONSRACTOR_D(&temp2, 2);
    SHELF_setBox(&aShelf, 2, &temp2);
    BOX_DISTRACTOR(&temp2);
    SHELF_print(&aShelf);
    printf("\n--- end doShelves() ---\n\n");
    for(int i = 0; i<3; i++){
        BOX_DISTRACTOR(&(aShelf.boxes[i]));
    }
}

int main() {
    BOX_CONSRACTOR_DDD(&largeBox, 10, 20, 30);
    printf("\n--- Start main() ---\n\n");
    doBoxes();
    thisFunc();
    thisFunc();
    thisFunc();
    thatFunc();
    thatFunc();
    doShelves();
    printf("\n--- End main() ---\n\n");
    BOX_DISTRACTOR(&box88);
    BOX_DISTRACTOR(&box99);
    BOX_DISTRACTOR(&largeBox);
    return 0;
}