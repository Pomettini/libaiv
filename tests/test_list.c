#include <aiv/list.h>
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

#define print_list (x) struct aiv_list_item item = x->head;\
while(item) {\
    fprintf(stdout, "%d\n", *(int *)item->data);\
    item = item->next;\
}\

int test_aiv_list_new()
{
    struct aiv_list *list = aiv_list_new(NULL);
    if (!list)
        return -1;

    aiv_list_destroy(list);
    return 0;
}

int test_aiv_list_append()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int element = 5;

    int ret = aiv_list_append(list, &element);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_append_null()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int ret = aiv_list_append(list, NULL);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_append_uniq()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int element = 666;
    
    int ret = aiv_list_append_uniq(list, &element);
    return ret;
}
    
int test_aiv_list_append_uniq_existent()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int element = 666;

    aiv_list_append_uniq(list, &element);
    int ret = aiv_list_append_uniq(list, &element);
    return ret;
}

int test_aiv_list_remove_empty()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;
    
    int ret = aiv_list_remove(list, NULL);
    aiv_list_destroy(list);
    return ret;
}


int test_aiv_list_remove()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    int ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }
    ret = aiv_list_remove(list, &a);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_two()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    const char* c = "ciao";
    int ret = 0;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_append(list, (void *)c);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, (void *)c);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_non_exsistent()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    const char* c = "ciao";
    int ret = 0;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, (void *)c);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_index_empty()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int ret = aiv_list_remove_index(list, 100);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_index()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
        if(!list)
            return -1;

    int ret = 0;
    int a = 768;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_index_two()
{
    struct aiv_list *list = aiv_list_new(NULL);
    if(!list)
        return -1;

    int ret = 0;
    int a = 768;
    const char* c = "hello";

    ret = aiv_list_append(list, (void*)c);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_iter()
{   
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    struct aiv_list_item *context = NULL;
    struct aiv_list_item *item = NULL;
    int counter = 0;

    int a = 345;

    int ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    while((item = aiv_list_iter(list, &context)))
    {
        counter++;
    }

    aiv_list_destroy(list);
    return counter;
}

int test_aiv_list_len()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int counter = 0;
    int ret = 0;

    int a = 666;
    int b = 111;

    aiv_list_append(list, &a);
    aiv_list_append(list, &b);

    return aiv_list_len(list);
}

int test_aiv_list_slow_len()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int counter = 0;
    int ret = 0;

    int a = 666;
    int b = 6666;
    int c = 66666;

    aiv_list_append(list, &a);
    aiv_list_append(list, &b);
    aiv_list_append(list, &c);

    return aiv_list_slow_len(list);
}

int test_aiv_list_contains()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int a = 666;

    aiv_list_append(list, &a);
    
    return aiv_list_contains(list, &a);
}

int test_aiv_list_contains_not()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int a = 666;
    int b = 6666;

    aiv_list_append(list, &a);
    
    return aiv_list_contains(list, &b);
}

int test_aiv_list_contains_at()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
    if(!list)
        return -1;

    int a = 666;
    int b = 6666;
    int c = 66666;

    aiv_list_append(list, &a);
    aiv_list_append(list, &b);
    aiv_list_append(list, &c);

    int element_pos = 0;
    // aiv_list_contains_at(list, &c, element_pos);

    aiv_list_destroy(list);
    
    return element_pos;
}

int test_aiv_list_shuffle()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    int b = 5;
    int c = 75;
    int d = 666;
    int e = 6666;

    int ret = 0;

    aiv_list_append(list, &a);
    aiv_list_append(list, &b);
    aiv_list_append(list, &c);
    aiv_list_append(list, &d);
    aiv_list_append(list, &e);

    aiv_list_shuffle(list);

    struct aiv_list_item* item = list->head;
    while(item)
    {
        fprintf(stdout, "%d\n", *(int *)item->data);
        item = item->next;
    }

    aiv_list_destroy(list);

    return 0;
}

int test_list_run()
{
    test(test_aiv_list_new);
    test(test_aiv_list_append);
    test(test_aiv_list_append_null);
    test(test_aiv_list_append_uniq);
    test_equal(test_aiv_list_append_uniq_existent, AIV_HAS_ELEMENT);
    test_equal(test_aiv_list_remove_empty, AIV_NOT_FOUND);
    test(test_aiv_list_remove);
    test(test_aiv_list_remove_two);
    test_equal(test_aiv_list_remove_non_exsistent, AIV_NOT_FOUND);
    test_equal(test_aiv_list_remove_index_empty, AIV_NOT_FOUND);
    test(test_aiv_list_remove_index);
    test(test_aiv_list_remove_index_two);
    test_equal(test_aiv_list_iter, 1);
    test_equal(test_aiv_list_len, 2);
    test_equal(test_aiv_list_slow_len, 3);
    test(test_aiv_list_contains);
    // test_equal(test_aiv_list_contains_not, AIV_NOT_FOUND);
    // test_equal(test_aiv_list_contains_at, 2);
    test(test_aiv_list_shuffle);

    fprintf(stdout, "list tests passed\n");
    return 0;
}