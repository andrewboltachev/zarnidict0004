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
    if (a->type != b->type) {
        return 0;
    } else {
        switch (a->type) {
            case NodeTypeInputChar:
                return *(a->content->input_char->value) == *(b->content->input_char->value);
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

/*int seq_node_len(SeqNode * seq_node) {
    SeqNode * this_seq_node = seq_node;
    int l = 0;
    while (this_seq_node != NULL) {
        l += 1;
    }
    return l;
}*/

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

#endif
