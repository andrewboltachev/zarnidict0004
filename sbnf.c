#include <stdlib.h>
#include <string.h>

enum AutomatonKind{AKChar};

typedef enum AutomatonKind AutomatonKindEnum;

struct AutomatonStruct {
    AutomatonKindEnum kind;
    char * name;
};

typedef struct AutomatonStruct Automaton;

Automaton * Char(const char * value, const char * name) {
    Automaton * st = malloc(sizeof(Automaton));
    st->kind = AKChar;
    strcpy(st->name, name);
    return st;
}

int foo(int a, int b) {
    return 4;
}
