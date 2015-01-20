#ifndef SBNF_H
#define SBNF_H

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef enum {AutomatonTypeChar, AutomatonTypeSeq} AutomatonType;

typedef struct {
    AutomatonType type;
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

typedef struct {
    struct Seq * next;
    Automaton * value;
} Seq;

InputChar * ic(wchar_t * value, void * payload) {
    InputChar * ichar = malloc(sizeof(InputChar));
    ichar->value = value;
    ichar->payload = payload;
    return ichar;
}

Automaton * Char(wchar_t * value, char * name) {
    Automaton * st = malloc(sizeof(Automaton));
    st->type = AutomatonTypeChar;
    st->name = (name == NULL) ? NULL : strdup(name);
    st->value = wcsdup(value);
    return st;
}


Seq * seq(Automaton * value, Seq * next, char * name) {
}

Automaton * a_seq(wchar_t * value, char * name) {
    Automaton * st = malloc(sizeof(Automaton));
    st->type = AutomatonTypeChar;
    st->name = (name == NULL) ? NULL : strdup(name);
    st->value = wcsdup(value);
    return st;
}


typedef union {
    InputChar *input_char;
} AutomatonResult;


int input_cmp(AutomatonResult * a, AutomatonResult * b) {
    return (a == b);
};

int foo(int a, int b) {
    return 4;
}

typedef enum {NodeTypeNode, NodeTypeSeqNode, NodeTypeInputChar} NodeType;


typedef struct SeqNode {
    struct Node * node;
    struct SeqNode * next;
} SeqNode;

typedef union NodeContent {
    struct Node * node;
    InputChar * input_char;
    SeqNode * seq_node;
} NodeContent;

typedef struct Node {
    NodeContent * content;
    NodeType type;
    char * name;
} Node;


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
            break;
        case NodeTypeNode:
            content->node = (Node*)data;
            break;
        case NodeTypeSeqNode:
            content->seq_node = (SeqNode*)data;
            break;
        default: {
        }
    }
    return make_node(content, type);
}

Node * node_node(Node *inner_node) {
    return make_node2(inner_node, NodeTypeNode);
}

int node_cmp(Node *a, Node *b) {
    if (a == NULL || b == NULL) {
        return (a == b);
    }
    if (a->type != b->type) {
        return 0;
    } else {
        switch (a->type) {
            case NodeTypeInputChar:
                return wcscmp(a->content->input_char->value, b->content->input_char->value) == 0;
            case NodeTypeNode:
                return node_cmp(a->content->node, b->content->node);
            case NodeTypeSeqNode: {
                SeqNode * this_a = a->content->seq_node;
                SeqNode * this_b = b->content->seq_node;
                while (!((this_a == NULL) && (this_b == NULL))) {
                    if (this_a != this_b) {
                        if (this_a == NULL || this_b == NULL) {
                            return 0;
                        }
                    }
                    if (!node_cmp(this_a->node, this_b->node)) {
                        return 0;
                    }
                    this_a = this_a->next;
                    this_b = this_b->next;
                }
                return 1;
            }
            default: {
                return 0;
            }
        }
    }
}

Node * node_ic(wchar_t * c, void * payload) {
    return make_node2(ic(c, payload), NodeTypeInputChar);
}


SeqNode * seqnode(Node * node, SeqNode * next) {
    SeqNode * seq_node = malloc(sizeof(SeqNode));
    seq_node->node = node;
    seq_node->next = next;
    return seq_node;
}


Node * node_seqnode(SeqNode * seq_node) {
    return make_node2(seq_node, NodeTypeSeqNode);
}

// run
Node * run(Automaton * a, InputChar * it[]) {
    if (wcscmp(a->value, it[0]->value) == 0) {
        Node * result = node_ic(a->value, NULL);
        return result;
    } else {
        return NULL;
    }
}

#endif
