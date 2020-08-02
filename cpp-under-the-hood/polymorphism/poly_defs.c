
#include "poly_defs.h"
#include <malloc.h>

TextFormatter_func TextFormatter_vmt = {TextFormatter_dtor, NULL};
DefaultTextFormatter_func DefaultTextFormatter_vmt = {{DefaultTextFormatter_dtor,virtual_DefaultTextFormatter_print}};
Multiplier_func Multiplier_vmt = {{{Multiplier_dtor, Multiplier_print}}};
PrePostFixer_func PrePostFixer_vmt = {{{PrePostFixer_dtor, PrePostFixer_print_c}}, PrePostFixer_print_lc, PrePostFixer_getDefaultSymbol};
PrePostDollarFixer_func PrePostDollarFixer_vmt = {{{{PrePostDollarFixer_dtor, PrePostFixer_print_c}}, PrePostDollarFixer_print_lc, PrePostDollarFixer_getDefaultSymbol}};
PrePostHashFixer_func PrePostHashFixer_vmt  = {{{{PrePostHashFixer_dtor, PrePostFixer_print_c}}, PrePostHashFixer_print_lc, PrePostHashFixer_getDefaultSymbol}};
PrePostFloatDollarFixer_func PrePostFloatDollarFixer_vmt = {{{{{PrePostFloatDollarFixer_dtor, PrePostFixer_print_c}}, PrePostDollarFixer_print_lc, PrePostFloatDollarFixer_getDefaultSymbol}}};
PrePostChecker_func PrePostChecker_vmt = {{{{{{PrePostChecker_dtor, PrePostFixer_print_c}}, PrePostDollarFixer_print_lc, PrePostFloatDollarFixer_getDefaultSymbol}}}};
static Ider ider;
void TextFormatter_dtor(void* const this){}
void DefaultTextFormatter_ctor(DefaultTextFormatter* const this){
    this->father.vptr = &DefaultTextFormatter_vmt;
    this->id = ider.next_id;
    ider.next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}
void DefaultTextFormatter_copy_ctor(DefaultTextFormatter* const this, const DefaultTextFormatter* const copy){
    this->father.vptr = copy->father.vptr;
    this->id = ider.next_id;
    ider.next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", copy->id, this->id);
}
DefaultTextFormatter* DefaultTextFormatter_eq_operator(DefaultTextFormatter* const this, const DefaultTextFormatter* const copy){
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", copy->id, this->id);
    return this;
}
void DefaultTextFormatter_dtor(void* const this){
    ((DefaultTextFormatter*)this)->father.vptr = &TextFormatter_vmt;
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", ((DefaultTextFormatter*)this)->id);
    TextFormatter_dtor((TextFormatter*)this);
}
void virtual_DefaultTextFormatter_print(const void* const this, const char* text){
    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}
DefaultTextFormatter* generateFormatterArray(){
    int i;
    DefaultTextFormatter* temp = (DefaultTextFormatter*)malloc(3* sizeof(DefaultTextFormatter));
    for(i = 0; i<3; i++){
        DefaultTextFormatter_ctor(&(temp[i]));
    }
    return temp;
}
void PrePostFixer_ctor(PrePostFixer* const this, const char* prefix, const char* postfix){
    DefaultTextFormatter_ctor(&(this->father));
    this->father.father.vptr = &PrePostFixer_vmt;
    this->pre = prefix;
    this->post = postfix;
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
}
void PrePostFixer_dtor(void* const this) {
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->pre, ((PrePostFixer*)this)->post);
    ((PrePostFixer*)this)->father.father.vptr = &TextFormatter_vmt;
    DefaultTextFormatter_dtor(&(((PrePostFixer*)this)->father));
}
void PrePostFixer_print_c(const void* const this, const char* text){
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", ((PrePostFixer*)this)->pre, text, ((PrePostFixer*)this)->post);
}
void PrePostFixer_print_lc(const void* const this, long num, char symbol){
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol){
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", ((PrePostFixer*)this)->pre, symbol, num, ((PrePostFixer*)this)->post);
    }
    else{
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", ((PrePostFixer*)this)->pre, num, ((PrePostFixer*)this)->post);
    }
}
char PrePostFixer_getDefaultSymbol(const void* const this){
    return '\0';
}
void PrePostDollarFixer_ctor(PrePostDollarFixer* const this, const char* prefix, const char* postfix){
    PrePostFixer_ctor(((PrePostFixer*)this), prefix, postfix);
    this->father.father.father.vptr = &PrePostDollarFixer_vmt;
    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", prefix, postfix);

}
void PrePostDollarFixer_copy_ctor(PrePostDollarFixer* const this, const PrePostDollarFixer* const copy){
    DefaultTextFormatter_copy_ctor(&(this->father.father), &(copy->father.father));
    this->father.pre = copy->father.pre;
    this->father.post = this->father.post;
    this->father.father.father.vptr = copy->father.father.father.vptr;
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->father.pre, this->father.post);
}
void PrePostDollarFixer_dtor(void* const this){
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostDollarFixer*)this)->father.pre, ((PrePostDollarFixer*)this)->father.post);
    ((PrePostDollarFixer*)this)->father.father.father.vptr = &PrePostFixer_vmt;
    PrePostFixer_dtor(this);
}
void PrePostDollarFixer_print_c(const PrePostDollarFixer* const this, int num, char symbol){
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");
    ((PrePostFixer_func*)this->father.father.father.vptr)->print_lc(this, num, symbol);
}
void PrePostDollarFixer_print_lc(const void* const this, long num, char symbol){
    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");
    PrePostFixer_print_lc(this, num, symbol);
}
void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol){
    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", this->father.pre, symbol, num, ((PrePostDollarFixer*)this)->father.post);
}
char PrePostDollarFixer_getDefaultSymbol(const void* const this){
    return '$';
}
void PrePostHashFixer_ctor(PrePostHashFixer* const this, int prc){
    PrePostDollarFixer_ctor((PrePostDollarFixer*)this, "===> ", " <===");
    this->father.father.father.father.vptr = &PrePostHashFixer_vmt;
    this->precision = prc;
    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->father.father.pre, this->father.father.post, this->precision);
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->father.father.pre, '#', this->precision, 9999.9999, this->father.father.post);
}
void PrePostHashFixer_dtor(void* const this){
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostHashFixer*)this)->father.father.pre, ((PrePostHashFixer*)this)->father.father.pre);
    ((PrePostHashFixer*)this)->father.father.father.father.vptr = &PrePostDollarFixer_vmt;
    PrePostDollarFixer_dtor(this);
}
void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol){
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->father.father.pre, symbol, this->precision, (double)num, this->father.father.post);
}
void PrePostHashFixer_print_lc(const void* const this, long num, char symbol){
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostHashFixer*)this)->father.father.pre, symbol, ((PrePostHashFixer*)this)->precision, (double )num, ((PrePostHashFixer*)this)->father.father.post);
}
void PrePostHashFixer_print_dc(const PrePostHashFixer* const this, double num, char symbol){
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->father.father.pre, symbol, this->precision, num, this->father.father.post);
}
char PrePostHashFixer_getDefaultSymbol(const void* const this){
    return '#';
}
void PrePostFloatDollarFixer_ctor(PrePostFloatDollarFixer* const this, const char* prefix, const char* postfix){
    PrePostDollarFixer_ctor((PrePostDollarFixer*)this, prefix, postfix);
    this->father.father.father.father.vptr = &PrePostFloatDollarFixer_vmt;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->father.father.pre, this->father.father.post);
}
void PrePostFloatDollarFixer_dtor(void* const this){
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFloatDollarFixer*)this)->father.father.pre,  ((PrePostFloatDollarFixer*)this)->father.father.post);
    ((PrePostFloatDollarFixer*)this)->father.father.father.father.vptr = &PrePostDollarFixer_vmt;
    PrePostDollarFixer_dtor(this);
}
void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const this, float num){
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");
    PrePostFloatDollarFixer_print_fc(this, num, '@');
}
void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const this, float num, char symbol){
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", this->father.father.pre, symbol, num, this->father.father.post);
}
char PrePostFloatDollarFixer_getDefaultSymbol(const void* const this){
    return '@';
}
void PrePostChecker_ctor(PrePostChecker* const this){
    PrePostDollarFixer_ctor((PrePostDollarFixer*)this, "[[[", "]]]");
    this->father.father.father.father.father.vptr = &PrePostChecker_vmt;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->father.father.father.pre, this->father.father.father.post);
}
void PrePostChecker_dtor(void* const this){
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostChecker*)this)->father.father.father.pre, ((PrePostChecker*)this)->father.father.father.post);
    ((PrePostChecker*)this)->father.father.father.father.father.vptr = &PrePostFloatDollarFixer_vmt;
    PrePostFloatDollarFixer_dtor(this);
}
void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", ((PrePostFixer_func*)this->father.father.father.father.father.vptr)->getDefaultSymbol(this));
}
void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");
    printf("Default symbol is %c\n", '@');
}
void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", ((PrePostFixer_func*)this->father.father.father.father.father.vptr)->getDefaultSymbol(this));
}
void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");
    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbol(this));
}
void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");
    printf("Default symbol is %c\n", '$');
}
void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");
    printf("Default symbol is %c\n", '$');
}
void Multiplier_ctor(Multiplier* const this, int t){
    DefaultTextFormatter_ctor((DefaultTextFormatter*)this);
    this->father.father.vptr = &Multiplier_vmt;
    this->times = t;
    printf("--- Multiplier CTOR: times = %d\n", this->times);
}
void Multiplier_dtor(void* const this){
    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)this)->times);
    ((Multiplier*)this)->father.father.vptr = &DefaultTextFormatter_vmt;
    DefaultTextFormatter_dtor(this);
}
void Multiplier_print(const void* const this, const char* text){
    int i;
    printf("%-60s | ", "[Multiplier::print(const char*)]");
    for (i = 0; i < ((Multiplier*)this)->times; ++i)
        printf("%s", text);
    printf("\n");
}
int Multiplier_getTimes(const Multiplier* const this){
    return this->times;
}
void Multiplier_setTimes(Multiplier* const this, int t){
    this->times = t;
}