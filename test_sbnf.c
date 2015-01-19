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
    na->content = ca;
    Node * nb = malloc(sizeof(Node));
    nb->content = cb;

    assert(1 != node_cmp(na, nb));
}

void test_input_cmp0002() {
    InputChar * a = ic(L"a", NULL);
    InputChar * b = ic(L"a", NULL);

    NodeContent * ca = malloc(sizeof(NodeContent));
    ca->input_char = a;
    NodeContent * cb = malloc(sizeof(NodeContent));
    cb->input_char = b;

    Node * na = malloc(sizeof(Node));
    na->content = ca;
    na->type = NodeTypeInputChar;
    Node * nb = malloc(sizeof(Node));
    nb->content = cb;
    nb->type = NodeTypeInputChar;

    assert(1 == node_cmp(na, nb));
}

void test_input_cmp0003() {
    InputChar * a = ic(L"a", NULL);
    InputChar * b = ic(L"a", NULL);

    NodeContent * ca = malloc(sizeof(NodeContent));
    ca->input_char = a;
    NodeContent * cb = malloc(sizeof(NodeContent));
    cb->input_char = b;

    Node * na = malloc(sizeof(Node));
    na->content = ca;
    na->type = NodeTypeInputChar;
    Node * nb = malloc(sizeof(Node));
    nb->content = cb;
    nb->type = NodeTypeInputChar;

    NodeContent * c1a = malloc(sizeof(NodeContent));
    ca->node = na;
    NodeContent * c1b = malloc(sizeof(NodeContent));
    cb->node = nb;

    Node * n1a = malloc(sizeof(Node));
    n1a->content = c1a;
    n1a->type = NodeTypeNode;
    Node * n1b = malloc(sizeof(Node));
    n1b->content = c1b;
    n1b->type = NodeTypeNode;

    assert(1 == node_cmp(na, nb));
}

void test_Char() {
    //char * v = "aaa";
    //Automaton * g = Char(L"ӹ", v);
}

int main() {
    run_test(test_input_cmp0001);
    run_test(test_input_cmp0002);
    //run_test(test_Char);
    return 0;
}
