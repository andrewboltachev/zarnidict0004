#include <stdio.h>
#include <assert.h>
#include "sbnf.h"

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

void test_foo() {
    assert(4 == foo(2, 2));
}

int main() {
    run_test(test_foo);
    return 0;
}
