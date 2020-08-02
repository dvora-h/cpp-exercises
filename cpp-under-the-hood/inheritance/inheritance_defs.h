/*
 Created by mby on 16/06/2020.
*/

#ifndef UTH_INHERITANCE_DEFS_H
#define UTH_INHERITANCE_DEFS_H

#include "box.h"
typedef enum Types
{
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
}Types;
typedef struct Materials{
    char padding;
}Materials;
const char* getName(Types types);


typedef struct Material_t{
    Types materials;
}Material_t;
void material_t_constractor(Material_t* mat, Types type);

typedef struct PhysicalBox{
    Box box;
    Material_t material;
}PhysicalBox;
void PhysicalBox_constractor_ddd(PhysicalBox* p, double l, double w, double h);
void PhysicalBox_constractor_dddt(PhysicalBox* p, double l, double w, double h, Types t);
void PhysicalBox_constractor_t(PhysicalBox* p, Types t);
void PhysicalBox_distractor(PhysicalBox* p);
void PhysicalBox_printp(const PhysicalBox*const p);

typedef struct WeightBox{
    Box box;
    double weight;
}WeightBox;

void WeightBox_constractor(WeightBox* weight, double l, double w, double h, double wgt);
void WeightBox_copy_constractor(WeightBox* wgt, const WeightBox* other);
void WeightBox_distractor(WeightBox* weight);
WeightBox* WeightBox_eq_operator(WeightBox* wb, const WeightBox* other);
void WeightBox_printw(const WeightBox* const weight);



#endif /*UTH_INHERITANCE_DEFS_H*/
