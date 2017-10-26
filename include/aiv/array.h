#include <string.h>
#include <stdlib.h>

struct aiv_array
{
    void **data;
    unsigned int len;
};

struct aiv_array *aiv_array_new(unsigned int, int *);
void aiv_array_destroy(struct aiv_array *);
int aiv_array_insert(struct aiv_array *, unsigned int, void *);
unsigned int aiv_array_len(struct aiv_array *);
int aiv_array_remove_at(struct aiv_array *, unsigned int);
void *aiv_array_at(struct aiv_array *array, unsigned int);