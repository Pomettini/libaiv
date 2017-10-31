#include <aiv/list.h>
#include <stdio.h>
#include <aiv/error.h>
#include <stdlib.h>

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
    list->length += 1;

    return AIV_OK;
}

int aiv_list_append_uniq(struct aiv_list *list, void *element)
{
    unsigned int counter = 0;
    struct aiv_list_item *item = list->head;
    while(item)
    {
        if (element == item->data)
            return AIV_HAS_ELEMENT;

        counter++;
        item = item->next;
    }
    
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
    list->length += 1;

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
    list->length -= 1;
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
            list->length += 1;

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
            list->length -= 1;
            
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

void aiv_list_get(struct aiv_list *list, void *element)
{
    
}

int aiv_list_len(struct aiv_list *list)
{
    return list->length;
}

int aiv_list_slow_len(struct aiv_list *list)
{
    unsigned int counter = 0;
    struct aiv_list_item *item = list->head;

    while(item)
    {
        counter++;
        item = item->next;
    }

    return counter;
}

int aiv_list_contains(struct aiv_list *list, void *element)
{
    unsigned int counter = 0;
    struct aiv_list_item *item = list->head;

    while(item)
    {
        if(element == item->data)
            return AIV_OK;

        counter++;
        item = item->next;
    }

    return AIV_NOT_FOUND;
}

int aiv_list_contains_at(struct aiv_list *list, void *element, unsigned int pos)
{
    unsigned int counter = 0;
    struct aiv_list_item *item = list->head;

    while(item)
    {
        if(element == item->data)
        {
            pos = counter;
            return AIV_OK;
        }

        counter++;
        item = item->next;
    }

    return AIV_NOT_FOUND;
}

// Duccio's shuffle implementation™
void aiv_list_shuffle(struct aiv_list *list)
{
    unsigned int len = aiv_list_len(list);
    if(len <= 1)
        return;

    struct aiv_list_item *item = list->head;
    struct aiv_list_item *start = list->head;

    unsigned int random = (unsigned int)((double)rand()/RAND_MAX * len);
    unsigned int i = 0;

    while (item)
    {
        if(i++ == random)
        {
            void *current_data = item->data;
            item->data = list->head->data;
            list->head->data = current_data;
            item = start->next;
            start = item;
            random = (unsigned int)((double)rand()/RAND_MAX * len);
            i = 0;
        }
        item = item->next;
    }
}

// void aiv_list_print(struct aiv_list *list)
// {
//     struct aiv_list_item *item = list->head;
//     while(item)
//     {
//         fprintf(stdout, "%d\n", item->data);
//         item = item->next; 
//     }
// }