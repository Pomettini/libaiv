#include <aiv/array.h>
#include <aiv/error.h>

struct aiv_array *aiv_array_new(unsigned int initial_size, int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;
    struct aiv_array *array = malloc(sizeof(struct aiv_array));
    if (!array)
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }
    memset(array, 0, sizeof(struct aiv_array));

    if (initial_size)
    {
        array->len = initial_size;
        array->data = malloc(sizeof(void *) * array->len);
        if (!array->data)
        {
            free(array);
            if (err_code)
                *err_code = AIV_NO_MEM;
            return NULL;
        }
        memset(array->data, 0, sizeof(void *) * array->len);
    }

    return list;
}

int aiv_array_insert(struct aiv_array *array, unsigned int index, void *element)
{
    if (index >= array->len)
    {
        void *new_data = realloc(array->data, sizeof(void *) * index + 1);
        if (!new_data)
        {
            return AIV_NO_MEM;
        }
        array->data = new_data;
        unsigned long remains = (sizeof(void *) * index + 1) - (sizeof(void *) * array->len);
        memset(array->data + sizeof(void *) * array->len, 0, remains);
        array->len = index + 1;
    }

    array->data[index] = element;
    return AIV_OK;
}

void aiv_array_destroy(struct aiv_array *array)
{
    free(array->data);
    free(array);
}