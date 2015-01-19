#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef enum {AKChar} AutomatonKind;

typedef struct {
    AutomatonKind kind;
    char * name;
    wchar_t * value;
} Automaton;

typedef struct {
    wchar_t * value;
    void * payload;
} InputChar;

typedef struct {
    InputChar ** input_chars;
    int count;
} Iterator;

InputChar * ic(wchar_t * value, void * payload) {
    InputChar * ichar = malloc(sizeof(InputChar));
    ichar->value = value;
    ichar->payload = payload;
    return ichar;
}

Automaton * Char(wchar_t * value, char * name) {
    Automaton * st = malloc(sizeof(Automaton));
    st->kind = AKChar;
    st->name = strdup(name);
    st->value = wcsdup(value);
    return st;
}


typedef union {
    InputChar *input_char;
} AutomatonResult;


int input_cmp(AutomatonResult * a, AutomatonResult * b) {
    return (a == b);
};

AutomatonResult * run(Automaton * a, Iterator * it) {

}

int foo(int a, int b) {
    return 4;
}

typedef union NodeContent {
    struct Node * node;
    InputChar * input_char;
} NodeContent;

typedef struct Node {
    NodeContent * content;
    char * name;
    char * klass;
} Node;


Node * node() {
    Node * n = malloc(sizeof(Node));
    return n;
}

int node_cmp(Node *a, Node *b) {
    return 0;
}

Node * node_ic(wchar_t * c) {
    InputChar * input_char = malloc(sizeof(InputChar));
    input_char->value = c;
    input_char->payload = NULL;
    NodeContent * node_content = malloc(sizeof(NodeContent));
    node_content->input_char = input_char;
    Node * node = malloc(sizeof(Node));
    node->content = node_content;
    return node;
}
