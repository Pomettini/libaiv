#include <string.h>
#include <stdlib.h>

typedef struct aiv_dict_item
{
    struct aiv_list_item *prev;
    struct aiv_list_item *next;
    void °key;
    unsigned int key_len;
    void *data;
};

typedef struct aiv_dict_item aiv_dict_item_t;

// Compact typedef
typedef struct aiv_dict
{
    struct aiv_dict_item **hash_map;
} aiv_dict_t;

// Create a new dictionary
aiv_dict_t *aiv_dict_new(unsigned int, int *);
// Add an item to a dictionary
int aiv_dict_add(aiv_dict *, void *, unsigned int, void *);
// Retrieve a value given a key
void *aiv_dict_get(aiv_dict *, void *, unsigned int);