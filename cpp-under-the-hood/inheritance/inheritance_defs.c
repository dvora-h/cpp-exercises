/*
 Created by mby on 16/06/2020.
*/
#include <stdio.h>
#include "inheritance_defs.h"
const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
/*const char* getName(Types types)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    return names[types];
}*/
void material_t_constractor(Material_t* mat, Types type){
    mat->materials = type;
    printf("Material created, set to %s\n", names[type]);
}
void PhysicalBox_constractor_ddd(PhysicalBox* p, double l, double w, double h){
    BOX_CONSRACTOR_DDD(&(p->box), l, w, h);
    material_t_constractor(&(p->material), OTHER);
    PhysicalBox_printp(p);
}
void PhysicalBox_constractor_dddt(PhysicalBox* p, double l, double w, double h, Types t){
    BOX_CONSRACTOR_DDD(&(p->box), l, w, h);
    material_t_constractor(&(p->material), t);
    PhysicalBox_printp(p);
}
void PhysicalBox_constractor_t(PhysicalBox* p, Types t){
    BOX_CONSRACTOR_D(&(p->box), 1);
    material_t_constractor(&(p->material), t);
    PhysicalBox_printp(p);
}
void PhysicalBox_distractor(PhysicalBox* p){
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", p->box.length, p->box.width, p->box.height, names[p->material.materials]);
    BOX_DISTRACTOR(&(p->box));
}
void PhysicalBox_printp(const PhysicalBox*const p){
    printf("PhysicalBox, made of %s; ", names[p->material.materials]);
    BOX_print(&(p->box));
}

void WeightBox_constractor(WeightBox* weight, double l, double w, double h, double wgt){
    BOX_CONSRACTOR_DDD(&(weight->box), l, w, h);
    weight-> weight = wgt;
    WeightBox_printw(weight);
}
void WeightBox_copy_constractor(WeightBox* wgt, const WeightBox* other){
    BOX_CONSRACTOR_D(&(wgt->box), 1);
    wgt->weight = other->weight;
    WeightBox_printw(wgt);
}
void WeightBox_distractor(WeightBox* weight){
    printf("Destructing WeightBox; ");
    WeightBox_printw(weight);
    BOX_DISTRACTOR(&(weight->box));
}
WeightBox* WeightBox_eq_operator(WeightBox* wb, const WeightBox* other){
    wb->weight = other->weight;
    return wb;
}
void WeightBox_printw(const WeightBox* const weight){
    printf("WeightBox, weight: %f; ", weight->weight);
    BOX_print(&(weight->box));
}
