#include <string.h>
#include <stdlib.h>

struct aiv_list_item
{
    struct aiv_list_item *prev;
    struct aiv_list_item *next;
    void *data;
};

struct aiv_list
{
    struct aiv_list_item *head;
    struct aiv_list_item *tail;
};

// create a new list
struct aiv_list *aiv_list_new(int *);
void aiv_list_destroy(struct aiv_list *);
// append a new element to the list
int aiv_list_append(struct aiv_list *, void *);
// remove the specified element from the list
int aiv_list_remove(struct aiv_list *, void *);
// remove the element at the specified index
int aiv_list_remove_index(struct aiv_list *, unsigned int);
// insert an element in the specified position
int aiv_list_insert(struct aiv_list *, unsigned int, void *);