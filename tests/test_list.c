#include <aiv/list.h>
#include <stdio.h>

#define test(x) if (x()) {\
    fprintf(stderr, "test failed while running function " #x "() at address %p line %d\n", x, __LINE__);\
    exit(1);\
}

int test_aiv_list_new()
{
    struct aiv_list *list = aiv_list_new(NULL);
    if (!list)
        return -1;
    return 0;

}

int main(int argc, char **argv)
{
    test(test_aiv_list_new);

    fprintf(stdout, "all tests passed\n");
    return 0;
}