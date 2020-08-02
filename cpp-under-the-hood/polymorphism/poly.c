
#include "poly_defs.h"
#include <malloc.h>
extern Multiplier_func Multiplier_vmt;
void doFormatterDynamicArray()
{
    int i, j;
    DefaultTextFormatter* formatters;
    printf("\n--- start doFormatterDynamicArray() ---\n\n");
    formatters = generateFormatterArray();
    printf("--------------------------------------\n");

    for (i = 0; i < 3; ++i){
        ((TextFormatter_func*)formatters[i].father.vptr)->print(&(formatters[i]), "Hello World!");
    }
    printf("\n--- end doFormatterDynamicArray() ---\n\n");
    for (j = 0; j < 3; ++j){
        printf("******************************\n");
        ((TextFormatter_func*)formatters[j].father.vptr)->dtor(&(formatters[j]));
    }
    free (formatters);
}

void doPrePostFixer(){
    PrePostFixer angleBrackets;
    printf("\n--- start doPrePostFixer() ---\n\n");
    PrePostFixer_ctor(&angleBrackets, "<<< ", " >>>");
    ((TextFormatter_func*)angleBrackets.father.father.vptr)->print(&angleBrackets, "Hello World!");
    ((PrePostFixer_func*)angleBrackets.father.father.vptr)->print_lc(&angleBrackets, -777, '\0');
    ((PrePostFixer_func*)angleBrackets.father.father.vptr)->print_lc(&angleBrackets, 350, '#');
    ((PrePostFixer_func*)angleBrackets.father.father.vptr)->print_lc(&angleBrackets, 3, '\0');
    printf("\n--- end doPrePostFixer() ---\n\n");
    ((TextFormatter_func*)angleBrackets.father.father.vptr)->dtor(&angleBrackets);
}
void doPrePostDollarFixer(){
    PrePostDollarFixer asterisks;
    printf("\n--- start doPrePostDollarFixer() ---\n\n");
    PrePostDollarFixer_ctor(&asterisks,"***** ", " *****");
    PrePostDollarFixer_print_c(&asterisks, -777, '$');
    PrePostDollarFixer_print_c(&asterisks, 350, '#');
    PrePostDollarFixer_print_dc(&asterisks, 3.14f,  '$');
    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&asterisks);
}
void runAsPrePostFixerRef(PrePostFixer* pp){
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    ((PrePostFixer_func*)pp->father.father.vptr)->print_lc(pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}
void runAsPrePostDollarFixerRef(PrePostDollarFixer* pp){
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");
    ((PrePostFixer_func*)pp->father.father.father.vptr)->print_lc(pp, 123, '$');
    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}
void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp){
    PrePostDollarFixer new;
    PrePostDollarFixer_copy_ctor(&new, &pp);
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");
    PrePostDollarFixer_print_c(&new, 123, '$');
    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
    PrePostDollarFixer_dtor((void*)&new);
}
void runAsPrePostHashFixerRef(const PrePostHashFixer* pp){
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");
    PrePostHashFixer_print_ic(pp, 123, ((PrePostFixer_func*)pp->father.father.father.father.vptr)->getDefaultSymbol(pp));
    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}
void doFormatterPtrs(){
    DefaultTextFormatter* pfmt[3];
    int i;
    printf("\n--- start doFormatterPtrs() ---\n\n");
    pfmt[0] = malloc(sizeof(PrePostDollarFixer));
    PrePostDollarFixer_ctor((PrePostDollarFixer*)pfmt[0], "!!! ", " !!!");
    pfmt[1] = malloc(sizeof(Multiplier));
    Multiplier_ctor((Multiplier*)pfmt[1], 4);
    pfmt[2] = malloc(sizeof(PrePostChecker));
    PrePostChecker_ctor((PrePostChecker*)pfmt[2]);
    printf("****************\n");
    for (i = 0; i < 3; ++i){
        ((TextFormatter_func*)pfmt[i]->father.vptr)->print(pfmt[i], "Hello World!");
    }

    for (i = 2; i >= 0; --i){
        ((TextFormatter_func*)pfmt[i]->father.vptr)->dtor(pfmt[i]);
        free(pfmt[i]);
    }
    printf("\n--- end doFormatterPtrs() ---\n\n");

}
void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    PrePostFloatDollarFixer_ctor(&hashes, "### ", " ###");
    PrePostFloatDollarFixer_print_f(&hashes, -777);
    PrePostFloatDollarFixer_print_fc(&hashes, 350, '#');
    PrePostFloatDollarFixer_print_f(&hashes, 3.14f);
    PrePostDollarFixer_copy_ctor(&hashes2, (PrePostDollarFixer*)&hashes);
    PrePostDollarFixer_print_dc(&hashes2, 7.5, '$');
    PrePostDollarFixer_print_c(&hashes2, 100, '$');
    printf("\n--- end doPrePostFloatDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&hashes2);
    PrePostFloatDollarFixer_dtor(&hashes);
}
void doPrePostChecker()
{
    PrePostChecker check;
    printf("\n--- start doPrePostChecker() ---\n\n");
    PrePostChecker_ctor(&check);
    PrePostChecker_printThisSymbolUsingFunc(&check);
    PrePostChecker_printThisSymbolDirectly(&check);
    PrePostChecker_printDollarSymbolByCastDirectly(&check);
    PrePostChecker_printDollarSymbolByScopeDirectly(&check);
    PrePostChecker_printDollarSymbolByCastUsingFunc(&check);
    PrePostChecker_printDollarSymbolByScopeUsingFunc(&check);
    printf("\n--- end doPrePostChecker() ---\n\n");
    PrePostChecker_dtor(&check);
}
void doMultiplier(){
    Multiplier m1, m2, m3, m4;
    printf("\n--- start doMultiplier() ---\n\n");
    DefaultTextFormatter_ctor((DefaultTextFormatter*)&m1);
    m1.father.father.vptr = &Multiplier_vmt;
    m1.times = 3;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    DefaultTextFormatter_ctor((DefaultTextFormatter*)&m2);
    m2.father.father.vptr = &Multiplier_vmt;
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", m2.times);
    DefaultTextFormatter_copy_ctor(&m3.father, &m1.father);
    m3.father.father.vptr = m1.father.father.vptr;
    m3.times = m1.times;
    DefaultTextFormatter_copy_ctor(&m4.father, &m2.father);
    m4.father.father.vptr = m2.father.father.vptr;
    m4.times = m2.times;
    Multiplier_print(&m1, "abc ");
    Multiplier_print(&m2, "abc ");
    Multiplier_print(&m3, "abc ");
    Multiplier_print(&m4, "abc ");
    printf("\n--- end doMultiplier() ---\n\n");
    Multiplier_dtor(&m4);
    Multiplier_dtor(&m3);
    Multiplier_dtor(&m2);
    Multiplier_dtor(&m1);
}
void doFormatterArray(){
    DefaultTextFormatter formatters[3];
    PrePostDollarFixer p;
    Multiplier m;
    PrePostChecker pc;
    int i;
    printf("\n--- start doFormatterArray() ---\n\n");
    PrePostDollarFixer_ctor(&p, "!!! ", " !!!");
    DefaultTextFormatter_copy_ctor(&formatters[0], (DefaultTextFormatter*)&p);
    PrePostDollarFixer_dtor(&p);
    Multiplier_ctor(&m, 4);
    DefaultTextFormatter_copy_ctor(&formatters[1], (DefaultTextFormatter*)&m);
    Multiplier_dtor(&m);
    PrePostChecker_ctor(&pc);
    DefaultTextFormatter_copy_ctor(&formatters[2], (DefaultTextFormatter*)&pc);
    PrePostChecker_dtor(&pc);
    for (i = 0; i < 3; ++i)
        virtual_DefaultTextFormatter_print(&formatters[i], "Hello World!");
    printf("\n--- end doFormatterArray() ---\n\n");
    DefaultTextFormatter_dtor(&formatters[2]);
    DefaultTextFormatter_dtor(&formatters[1]);
    DefaultTextFormatter_dtor(&formatters[0]);
}
int main(){
    PrePostHashFixer hfix;
    printf("\n--- Start main() ---\n\n");
    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();
    PrePostHashFixer_ctor(&hfix, 4);
    runAsPrePostFixerRef((PrePostFixer*)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer*)&hfix);
    runAsPrePostDollarFixerObj(hfix.father);
    runAsPrePostHashFixerRef(&hfix);
    doMultiplier();
    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();
    printf("\n--- End main() ---\n\n");
    PrePostHashFixer_dtor(&hfix);
    return 0;
}
