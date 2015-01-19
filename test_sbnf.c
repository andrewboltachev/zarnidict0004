#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sbnf.h"

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

void test_input_cmp0001() {
    InputChar * a = ic(L"a", NULL);
    InputChar * b = ic(L"b", NULL);
    NodeContent * ca = malloc(sizeof(NodeContent));
    ca->input_char = a;
    NodeContent * cb = malloc(sizeof(NodeContent));
    cb->input_char = b;
    Node * na = malloc(sizeof(Node));
    Node * nb = malloc(sizeof(Node));
    assert(1 != node_cmp(na, nb));
}

void test_input_cmp0002() {
    //InputChar * a = ic(L"a", NULL);
    //InputChar * a = ic(L"a", NULL);
    //assert(1 != node_cmp(na, nb));
}

void test_Char() {
    char * v = "aaa";
    Automaton * g = Char(L"ӹ", v);
    /*InputChar * x = {
        ic(L"", NULL)
    };
    AutomatonResult * r = run(g, x);
    assert(4 == foo(2, 2));*/
}

int main() {
    run_test(test_input_cmp0001);
    run_test(test_input_cmp0002);
    //run_test(test_Char);
    return 0;
}
