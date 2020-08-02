
#ifndef UTH_POLY_DEFS_H
#define UTH_POLY_DEFS_H

#include <stdio.h>
struct TextFormatter;
typedef struct TextFormatter_func{
    void (*dtor)(void* const);
    void (*print)(const void* const, const char*);
}TextFormatter_func;
typedef struct TextFormatter{
    void* vptr;
}TextFormatter;
void TextFormatter_dtor(void* const this);
struct DefaultTextFormatter;
typedef struct DefaultTextFormatter_func{
    TextFormatter_func father_func;
}DefaultTextFormatter_func;
typedef struct DefaultTextFormatter{
    TextFormatter father;
    int id;
}DefaultTextFormatter;
void DefaultTextFormatter_ctor(DefaultTextFormatter* const this);
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter* const this, const DefaultTextFormatter* const copy);
DefaultTextFormatter* DefaultTextFormatter_eq_operator(DefaultTextFormatter* const this, const DefaultTextFormatter* const copy);
void DefaultTextFormatter_dtor(void* const this);
void virtual_DefaultTextFormatter_print(const void* const this, const char* text);
DefaultTextFormatter* generateFormatterArray();

typedef struct Ider{
    int next_id;
}Ider;
struct PrePostFixer;
typedef struct PrePostFixer_func{
    DefaultTextFormatter_func father_func;
    void (*print_lc)(const void* const, long, char);
    char (*getDefaultSymbol)(const void* const);
}PrePostFixer_func;
typedef struct PrePostFixer{
    DefaultTextFormatter father;
    const char* pre;
    const char* post;
}PrePostFixer;
void PrePostFixer_ctor(PrePostFixer* const this,const char* prefix, const char* postfix);
void PrePostFixer_dtor(void* const this);
void PrePostFixer_print_c(const void * const this, const char* text);
void PrePostFixer_print_lc(const void* const this, long num, char symbol);
char PrePostFixer_getDefaultSymbol(const void* const this);
struct PrePostDollarFixer;
typedef struct PrePostDollarFixer_func{
    PrePostFixer_func father_func;
}PrePostDollarFixer_func;
typedef struct PrePostDollarFixer{
    PrePostFixer father;
}PrePostDollarFixer;
void PrePostDollarFixer_ctor(PrePostDollarFixer* const this, const char* prefix, const char* postfix);
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer* const this, const PrePostDollarFixer* const copy);
void PrePostDollarFixer_dtor(void* const this);
void PrePostDollarFixer_print_c(const PrePostDollarFixer* const this, int num, char symbol);
void PrePostDollarFixer_print_lc(const void* const this, long num, char symbol);
void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol);
char PrePostDollarFixer_getDefaultSymbol(const void* const this);
struct PrePostHashFixer;
typedef struct PrePostHashFixer_func{
    PrePostFixer_func father_func;
}PrePostHashFixer_func;
typedef struct PrePostHashFixer{
    PrePostDollarFixer father;
    int precision;
}PrePostHashFixer;
void PrePostHashFixer_ctor(PrePostHashFixer* const this, int prc);
void PrePostHashFixer_dtor(void* const this);
void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol);
void PrePostHashFixer_print_lc(const void* const this, long num, char symbol);
void PrePostHashFixer_print_dc(const PrePostHashFixer* const this, double num, char symbol);
char PrePostHashFixer_getDefaultSymbol(const void* const this);
typedef struct PrePostFloatDollarFixer_func{
    PrePostDollarFixer_func father_func;
}PrePostFloatDollarFixer_func;

typedef struct PrePostFloatDollarFixer{
    PrePostDollarFixer father;
}PrePostFloatDollarFixer;
void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer* const this, const char* prefix, const char* postfix);
void PrePostFloatDollarFixer_dtor(void* const);
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const, float num);
void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const, float num, char symbol);
char PrePostFloatDollarFixer_getDefaultSymbol(const void* const);
typedef struct PrePostChecker_func{
    PrePostFloatDollarFixer_func father_func;
}PrePostChecker_func;
typedef struct PrePostChecker{
    PrePostFloatDollarFixer father;
}PrePostChecker;
void PrePostChecker_ctor(PrePostChecker* const this);
void PrePostChecker_dtor(void* const this);
void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker* const);
void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const);
void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker* const);
void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const);
void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const);
void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const);
typedef struct Multiplier_func{
    DefaultTextFormatter_func father_func;
}Multiplier_func;
typedef struct Multiplier{
    DefaultTextFormatter father;
    int times;
}Multiplier;
void Multiplier_ctor(Multiplier* const this, int t);
void Multiplier_dtor(void* const this);
void Multiplier_print(const void* const this, const char* text);
int Multiplier_getTimes(const Multiplier*const this);
void Multiplier_setTimes(Multiplier* const this, int t);

#endif /*UTH_POLY_DEFS_H*/
