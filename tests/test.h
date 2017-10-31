#include <stdio.h>
#include <aiv/error.h>

#define test(x) if (x())                                                                                     \
    {                                                                                                        \
        fprintf(stderr, "test failed while running function " #x "() at address %p line %d\n", x, __LINE__); \
        exit(1);                                                                                             \
    \
}\

#define test_equal(x, y) {\
        int ret = x();\
        if (ret != y)\
        {\
            fprintf(stderr, "test failed while running function " #x "() at address %p line %d, expecting %d got %d\n", x, __LINE__, y, ret);\
            exit(1);\
        }\
    }