#ifndef SBNF_H
#define SBNF_H

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
    return NULL;
}

int foo(int a, int b) {
    return 4;
}

typedef enum {NodeTypeNode, NodeTypeSeqNode, NodeTypeInputChar} NodeType;

typedef union NodeContent {
    struct Node * node;
    InputChar * input_char;
} NodeContent;

typedef struct Node {
    NodeContent * content;
    NodeType type;
    char * name;
} Node;


typedef struct SeqNode {
    NodeContent * content;
    NodeType type;
    char * name;
    struct SeqNode * next;
} SeqNode;


Node * make_node(NodeContent * content, NodeType type) {
    Node * node = malloc(sizeof(Node));
    node->content = content;
    node->type = type;
    return node;
}

Node * make_node2(void * data, NodeType type) {
    NodeContent * content = malloc(sizeof(NodeContent));
    switch (type) {
        case NodeTypeInputChar:
            content->input_char = (InputChar*)data;
        case NodeTypeNode:
            content->node = (Node*)data;
        default: {
        }
    }
    return make_node(content, type);
}

Node * node_node(Node *inner_node) {
    return make_node2(inner_node, NodeTypeNode);
}

int node_cmp(Node *a, Node *b) {
    if (a->type != b->type) {
        return 0;
    } else {
        switch (a->type) {
            case NodeTypeInputChar:
                return *(a->content->input_char->value) == *(b->content->input_char->value);
            case NodeTypeNode:
                return node_cmp(a->content->node, b->content->node);
            default: {
                return 0;
            }
        }
    }
}

Node * node_ic(wchar_t * c, void * payload) {
    return make_node2(ic(c, payload), NodeTypeInputChar);
}
#endif
