#ifndef SBNF_H
#define SBNF_H

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef enum {AutomatonTypeChar, AutomatonTypeSeq} AutomatonType;


typedef struct {
    struct SeqEl * next;
    struct Automaton * value;
} SeqEl;

typedef union {
    wchar_t * char_value;
    SeqEl * seq_value;
} AutomatonContent;

typedef struct {
    AutomatonType type;
    char * name;
    AutomatonContent * content;
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

Automaton * make_automaton(AutomatonContent * content, AutomatonType type, char * name) {
    Automaton * st = malloc(sizeof(Automaton));
    st->type = type;
    st->name = (name == NULL) ? NULL : strdup(name);
    st->content = content;
    return st;
}

Automaton * make_automaton2(void * data, AutomatonType type, char * name) {
    AutomatonContent * ac = malloc(sizeof(AutomatonContent));
    switch (type) {
        case AutomatonTypeChar:
            ac->char_value = (wchar_t*)data;
        case AutomatonTypeSeq:
            ac->seq_value = (SeqEl*)data;
        default: {
        }
    }
    return make_automaton(ac, type, name);
}

Automaton * Char(wchar_t * value, char * name) {
    return make_automaton2(value, AutomatonTypeChar, name);
}


SeqEl * seq(Automaton * value, SeqEl * next) {
}

SeqEl * seq_el(Automaton * value, SeqEl * next) {
    SeqEl * seq_el = malloc(sizeof(SeqEl));
    seq_el->value = (struct Automaton*)value;
    seq_el->next = (struct SeqEl*)next;
    return seq_el;
}

Automaton * Seq(SeqEl * seq_el, char * name) {
    return make_automaton2(seq_el, AutomatonTypeSeq, name);
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

typedef struct {
    Node * node;
    int index;
} AutomatonResult;


AutomatonResult * ar(int index, Node * node) {
    AutomatonResult * ar = malloc(sizeof(AutomatonResult));
    ar->node = node;
    ar->index = index;
    return ar;
}

// run
AutomatonResult * process(Automaton * a, InputChar * it[], int len) {
    switch (a->type) {
        case AutomatonTypeChar:
            if (wcscmp(a->content->char_value, it[0]->value) == 0) {
                Node * result = node_ic(a->content->char_value, NULL);
                return ar(0, result);
            } else {
                return NULL;
            }
        case AutomatonTypeSeq:
            /*printf("%p\n", it);
            printf("%p\n", it + len);
            printf("%zu\n", sizeof(it));*/
            //a->content->seq_value; // SeqEl
            return NULL;
    }
}
Node * run(Automaton * a, InputChar * it[], int len) {
    AutomatonResult * ar = process(a, it, len);
    if (ar == NULL) {
        return NULL;
    } else {
        return ar->node;
    }
}
#endif
