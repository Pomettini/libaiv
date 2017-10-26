#include <aiv/list.h>
#include <aiv/error.h>

struct aiv_list *aiv_list_new(int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;
    struct aiv_list *list = malloc(sizeof(struct aiv_list));
    if (!list) {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }
    memset(list, 0, sizeof(struct aiv_list));
    return list;
}

int aiv_list_append(struct aiv_list *list, void *element)
{
    struct aiv_list_item *list_item = malloc(sizeof(struct aiv_list_item));
    if (!list_item)
    {
        return AIV_NO_MEM;
    }
    list_item->prev = list->tail;
    list_item->next = NULL;
    list_item->data = element;

    if (list_item->prev)
    {
        list_item->prev->next = list_item;
    }

    if (!list->head)
    {
        list->head = list_item;
    }

    list->tail = list_item;

    return AIV_OK;
}

void aiv_list_destroy(struct aiv_list *list)
{
    struct aiv_list_item *item = list->head;
    while(item)
    {
        struct aiv_list_item *next = item->next;
        free(item);
        item = next; 
    }
    free(list);
}

int aiv_list_remove(struct aiv_list *list, void *element)
{
    struct aiv_list_item *item = list->head;
    while(item)
    {
        if(element == item->data)
        {
            if(item == list->head)
            {
                list->head = item->next;
            }

            if(item == list->tail)
            {
                list->tail = item->prev;
            }

            if(item->prev)
            {
                item->prev->next = item->next;
            }

            if(item->next)
            {
                item->next->prev = item->prev;
            }

            free(item);

            return AIV_OK;
        }
        item = item->next;
         
    }
    return AIV_NOT_FOUND;
}

int aiv_list_remove_index(struct aiv_list *list, unsigned int index)
{
    unsigned int counter = 0;
    struct aiv_list_item *item = list->head;
    while(item)
    {
        if(counter == index)
        {
            if(item == list->head)
            {
                list->head = item->next;
            }

            if(item == list->tail)
            {
                list->tail = item->prev;
            }

            if(item->prev)
            {
                item->prev->next = item->next;
            }

            if(item->next)
            {
                item->next->prev = item->prev;
            }

            free(item);

            return AIV_OK;
        }
        counter++;
        item = item->next;
    }
    return AIV_NOT_FOUND;
}

struct aiv_list_item *aiv_list_iter(struct aiv_list *list, struct aiv_list_item **context)
{
    if (list->is_iterating && !*context) {
        list->is_iterating = 0;
        return NULL;
    }
    
    if (!*context) {
        list->is_iterating = 1;
        *context = list->head;
        return *context;
    }

    *context = (*context)->next;
    return *context;
}
