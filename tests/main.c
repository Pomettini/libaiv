#include <stdio.h>

void test_list_run();
void test_dict_run();

int main(int argc, char **argv)
{
    test_list_run();
    test_dict_run();

    fprintf(stdout, "all tests passed\n");
}