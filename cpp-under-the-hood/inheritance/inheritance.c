/*
 Created by mby on 16/06/2020.
*/
#include <stdio.h>
#include "inheritance_defs.h"
extern const char* const names[];

void doMaterials(){
    printf("\n--- Start doMaterials() ---\n\n");
    Materials mat;
    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n", sizeof(Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));
    struct MatTest {Materials mat;  Material_t mat_t; };
    printf("Size of Materials + Material_t: %lu\n", sizeof(struct MatTest));
    Material_t mat1;
    material_t_constractor(&mat1, OTHER);
    Material_t mat2;
    material_t_constractor(&mat2, METAL);
    printf("\n--- End doMaterials() ---\n\n");
}
void doPhysicalBox(){
    printf("\n--- Start doPhysicalBox() ---\n\n");
    PhysicalBox pb1;
    PhysicalBox_constractor_dddt(&pb1, 8, 6, 4, PLASTIC);
    PhysicalBox pb2;
    PhysicalBox_constractor_t(&pb2, WOOD);
    PhysicalBox pb3;
    PhysicalBox_constractor_ddd(&pb3, 7, 7, 7);
    printf("\npb4 is copy-constructed from pb1\n");
    PhysicalBox pb4 = pb1;
    PhysicalBox_printp(&pb4);
    PhysicalBox_printp(&pb1);
    printf("pb4 %s pb1\n", pb4.box.length == pb1.box.length && pb4.box.width == pb1.box.width && pb4.box.height == pb1.box.height && pb4.material.materials == pb1.material.materials? "equals" : "does not equal");
    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    PhysicalBox_printp(&pb4);
    PhysicalBox_printp(&pb3);
    printf("pb4 %s pb3\n", pb4.box.length == pb3.box.length && pb4.box.width == pb3.box.width && pb4.box.height == pb3.box.height && pb4.material.materials == pb3.material.materials? "equals" : "does not equal");
    printf("\n--- End doPhysicalBox() ---\n\n");
    PhysicalBox_distractor(&pb4);
    PhysicalBox_distractor(&pb3);
    PhysicalBox_distractor(&pb2);
    PhysicalBox_distractor(&pb1);
}

void doWeightBox(){
    printf("\n--- Start doWeightBox() ---\n\n");
    WeightBox pw1;
    WeightBox_constractor(&pw1, 8, 6, 4, 25);
    WeightBox pw2;
    WeightBox_constractor(&pw2, 1, 2, 3, 0.0);
    WeightBox pw3;
    WeightBox_constractor(&pw3, 10, 20, 30, 15);
    printf("\npw4 is copy-constructed from pw1\n");
    WeightBox pw4;
    WeightBox_copy_constractor(&pw4, &pw1);
    WeightBox_printw(&pw4);
    WeightBox_printw(&pw1);
    printf("pw4 %s pw1\n",  pw4.box.length == pw1.box.length && pw4.box.width == pw1.box.width && pw4.box.height == pw1.box.height && pw4.weight == pw1.weight ? "equals" : "does not equal");
    printf("\npw4 is copy-assigned from pw3\n");
    WeightBox_eq_operator(&pw4, &pw3);
    WeightBox_printw(&pw4);
    WeightBox_printw(&pw3);
    printf("pw4 %s pw1\n",  pw4.box.length == pw3.box.length && pw4.box.width == pw3.box.width && pw4.box.height == pw3.box.height && pw4.weight == pw3.weight ? "equals" : "does not equal");
    printf("\n--- End doWeightBox() ---\n\n");
    WeightBox_distractor(&pw4);
    WeightBox_distractor(&pw3);
    WeightBox_distractor(&pw2);
    WeightBox_distractor(&pw1);
}

int main() {
    printf("\n--- Start main() ---\n\n");
    doMaterials();
    doPhysicalBox();
    doWeightBox();
    printf("\n--- End main() ---\n\n");
    return 0;
}