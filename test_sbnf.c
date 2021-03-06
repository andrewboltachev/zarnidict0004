#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include "sbnf.h"


#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

// TODO: split "create" tests from cmp test?
void test_input_cmp0001() {
    InputChar * a = ic(L"a", NULL);
    InputChar * b = ic(L"b", NULL);

    NodeContent * ca = malloc(sizeof(NodeContent));
    ca->input_char = a;
    NodeContent * cb = malloc(sizeof(NodeContent));
    cb->input_char = b;

    Node * na = malloc(sizeof(Node));
    na->content = ca;
    na->type = NodeTypeInputChar;
    Node * nb = malloc(sizeof(Node));
    nb->content = cb;
    na->type = NodeTypeInputChar;

    assert(1 != node_cmp(node_ic(L"a", NULL), node_ic(L"b", NULL)));
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
    assert(1 == node_cmp(node_ic(L"a", NULL), node_ic(L"a", NULL)));
}

void test_input_cmp0003() {
    InputChar * a = ic(L"a", NULL);
    InputChar * b = ic(L"b", NULL);

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
    c1a->node = na;
    NodeContent * c1b = malloc(sizeof(NodeContent));
    c1b->node = nb;

    Node * n1a = malloc(sizeof(Node));
    n1a->content = c1a;
    n1a->type = NodeTypeNode;
    Node * n1b = malloc(sizeof(Node));
    n1b->content = c1b;
    n1b->type = NodeTypeNode;

    assert(1 != node_cmp(n1a, n1b));
}

void test_input_cmp0004() {
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
    c1a->node = na;
    NodeContent * c1b = malloc(sizeof(NodeContent));
    c1b->node = nb;

    Node * n1a = malloc(sizeof(Node));
    n1a->content = c1a;
    n1a->type = NodeTypeNode;
    Node * n1b = malloc(sizeof(Node));
    n1b->content = c1b;
    n1b->type = NodeTypeNode;

    assert(1 == node_cmp(n1a, n1b));
    assert(1 == node_cmp(node_node(node_ic(L"a", NULL)), node_node(node_ic(L"a", NULL))));
}

void test_input_cmp0005() {
    Node * a = node_ic(L"a", NULL);
    Node * b = node_ic(L"b", NULL);
    Node * c = node_ic(L"c", NULL);
    Node * d = node_ic(L"d", NULL);
    assert(1 != node_cmp(
        node_seqnode(seqnode(a, seqnode(b, seqnode(c, NULL)))),
        node_seqnode(seqnode(a, seqnode(b, seqnode(d, NULL))))
    ));
}

void test_input_cmp0006() {
    Node * a = node_ic(L"a", NULL);
    Node * b = node_ic(L"b", NULL);
    Node * c = node_ic(L"c", NULL);
    assert(1 == node_cmp(
        node_seqnode(seqnode(a, seqnode(b, seqnode(c, NULL)))),
        node_seqnode(seqnode(a, seqnode(b, seqnode(c, NULL))))
    ));
}

void test_input_cmp0007() {
    Node * a = node_ic(L"a", NULL);
    Node * b = node_ic(L"b", NULL);
    Node * c = node_ic(L"c", NULL);
    assert(1 != node_cmp(
        node_seqnode(seqnode(a, seqnode(b, seqnode(c, NULL)))),
        node_seqnode(seqnode(a, seqnode(b, NULL)))
    ));
}

void test_Char_0001() {
    Automaton * g = Char(L"a", NULL);
    InputChar * it[] = {ic(L"a", NULL)};
    Node * n = node_ic(L"a", NULL);
    assert(1 == node_cmp(run(g, it, 1), n));
}

void test_Char_0002() {
    Automaton * g = Char(L"ӱ", NULL);
    InputChar * it[] = {ic(L"ӱ", NULL)};
    Node * n = node_ic(L"ӱ", NULL);
    assert(1 == node_cmp(run(g, it, 1), n));
}

void test_Char_0003() {
    Automaton * g = Char(L"ӹ", NULL);
    InputChar * it[] = {ic(L"ӱ", NULL)};
    assert(1 == node_cmp(run(g, it, 1), NULL));
}

void test_Char_0004() {
    Automaton * g = Char(L"ӹ", NULL);
    InputChar * it[] = {ic(L"ӱ", NULL)};
    assert(1 == node_cmp(run(g, it, 1), NULL));
}

void test_Seq_0001() {
    Automaton * y = Char(L"ӹ", NULL);
    Automaton * a = Char(L"ӓ", NULL);

    Automaton * g = Seq(seq_el(y, seq_el(a, NULL)), NULL);
    InputChar * it[] = {ic(L"ӹ", NULL), ic(L"ӓ", NULL)};

    Node * yy = node_ic(L"ӹ", NULL);
    Node * aa = node_ic(L"ӓ", NULL);

    Node * n = node_seqnode(seqnode(yy, seqnode(aa, NULL)));
    Node * o = run(g, it, 2);
    print_node(o);
    print_node(n);

    assert(1 == node_cmp(o, n));
}

void test_Seq_0002() {
    Automaton * y = Char(L"ӹ", NULL);

    Automaton * g = Seq(seq_el(y, seq_el(y, NULL)), NULL);
    InputChar * it[] = {ic(L"ӹ", NULL), ic(L"ӓ", NULL)};

    Node * yy = node_ic(L"ӹ", NULL);
    Node * aa = node_ic(L"ӓ", NULL);

    Node * n = node_seqnode(seqnode(yy, seqnode(aa, NULL)));
    Node * o = run(g, it, 2);
    print_node(o);

    assert(NULL == o);
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    run_test(test_input_cmp0001);
    run_test(test_input_cmp0002);
    run_test(test_input_cmp0003);
    run_test(test_input_cmp0004);
    run_test(test_input_cmp0005);
    run_test(test_input_cmp0006);
    run_test(test_input_cmp0007);

    run_test(test_Char_0001);
    run_test(test_Char_0002);
    run_test(test_Char_0003);
    run_test(test_Char_0004);

    run_test(test_Seq_0001);
    run_test(test_Seq_0002);

    return 0;
}
