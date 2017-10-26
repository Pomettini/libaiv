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
    int is_iterating;
};

// create a new list
struct aiv_list *aiv_list_new(int *);
void aiv_list_destroy(struct aiv_list *);
// append a new element to the list
int aiv_list_append(struct aiv_list *, void *);
// append a new element to the list (unique version)
int aiv_list_append_uniq(struct aiv_list *, void *);
// remove the specified element from the list
int aiv_list_remove(struct aiv_list *, void *);
// remove the element at the specified index
int aiv_list_remove_index(struct aiv_list *, unsigned int);
// insert an element in the specified position
int aiv_list_insert(struct aiv_list *, unsigned int, void *);
// insert an element in the specified position (unique version)
int aiv_list_insert_uniq(struct aiv_list *, unsigned int, void *);
// iterator pattern
struct aiv_list_item *aiv_list_iter(struct aiv_list *, struct aiv_list_item **);
// check if the list contains the item
int aiv_list_contains(struct aiv_list *, void *);
// check if the list contains the specified item at the specified index
int aiv_list_contains_at(struct aiv_list *, void *, unsigned int);
// get the length of the list (optimized version)
int aiv_list_len(struct aiv_list *);
// get the length of the list (slow version)
int aiv_list_slow_len(struct aiv_list *);
// shuffle the list
void aiv_list_shuffle(struct aiv_list *);
// sort the list (if the sort func is NULL order by the address of the element)
// the sort function returns 0 on equality, -1 if the left arg wins, 1 for the second one
void aiv_list_sort(struct aiv_list *, int (*)(void *, void *));
// reverse the list
void aiv_list_reverse(struct aiv_list *);
// return a new list (copy) with the item starting from the specified item
struct aiv_list *aiv_list_sublist(struct aiv_list *, unsigned int);
// return the element of a list at an index
void aiv_list_get(struct aiv_list *, void *);