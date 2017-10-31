#include <aiv/dict.h>
#include <aiv/error.h>

#include <stdio.h>

// Bernstein classic hash
static unsigned int djb33x_hash(void *key, unsigned int key_len)
{

    unsigned int hash = 5381;
    unsigned int i;

    unsigned char *key_as_num = (unsigned char *)key;

    for (i = 0; i < key_len; i++)
    {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }

    return hash;
}

aiv_dict_t *aiv_dict_new(unsigned int hash_map_size, int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;

    if (hash_map_size < 1)
    {
        if (err_code)
            *err_code = AIV_INVALID_SIZE;
        return NULL;
    }

    aiv_dict_t *dict = malloc(sizeof(aiv_dict_t));
    if (!dict)
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }
    memset(dict, 0, sizeof(aiv_dict_t));

    dict->hash_map_size = hash_map_size;

    dict->hash_map = malloc(sizeof(aiv_dict_item_t *) * dict->hash_map_size);
    if (!dict->hash_map)
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        free(dict);
        return NULL;
    }

    // clear the hash map
    memset(dict->hash_map, 0, sizeof(aiv_dict_item_t *) * dict->hash_map_size);

    return dict;
}

int aiv_dict_add(aiv_dict_t *dict, void *key, unsigned int key_len, void *data)
{
    unsigned int hash = djb33x_hash(key, key_len) % (dict->hash_map_size - 1);

    fprintf(stdout, "hash of %.*s = %u\n", key_len, key, hash);

    if (!dict->hash_map[hash])
    {
        dict->hash_map[hash] = malloc(sizeof(aiv_dict_item_t));
        if (!dict->hash_map[hash])
        {
            return AIV_NO_MEM;
        }
        memset(dict->hash_map[hash], 0, sizeof(aiv_dict_item_t));
        fprintf(stdout, "created new hash record at %p\n", dict->hash_map[hash]);
        void *key_copy = malloc(key_len);
        if (!key_copy)
        {
            free(dict->hash_map[hash]);
            dict->hash_map[hash] = NULL;
            return AIV_NO_MEM;
        }
        memcpy(key_copy, key, key_len);
        dict->hash_map[hash]->key = key_copy;
        dict->hash_map[hash]->key_len = key_len;
        dict->hash_map[hash]->data = data;
        return 0;
    }
    else
    {
        aiv_dict_item_t *item = dict->hash_map[hash];
        aiv_dict_item_t *old_item = NULL;
        while (item)
        {
            old_item = item;
            if (key_len == item->key_len && !memcmp(item->key, key, key_len))
            {
                item->data = data;
                return AIV_OK;
            }
            item = item->next;
        }
        // now old_item points to the last element in the hash_map record
        aiv_dict_item_t *new_item = malloc(sizeof(aiv_dict_item_t));
        if (!new_item)
        {
            return AIV_NO_MEM;
        }
        memset(new_item, 0, sizeof(aiv_dict_item_t));
        fprintf(stdout, "created new hash record at %p after %p\n", new_item, old_item);
        void *key_copy = malloc(key_len);
        if (!key_copy)
        {
            free(new_item);
            return AIV_NO_MEM;
        }
        memcpy(key_copy, key, key_len);
        new_item->key = key_copy;
        new_item->key_len = key_len;
        new_item->data = data;

        old_item->next = new_item;
        new_item->prev = old_item;

        return AIV_OK;
    }

    return 0;
}

void *aiv_dict_get(aiv_dict_t *dict, void *key, unsigned int key_len)
{
    unsigned int hash = djb33x_hash(key, key_len) % (dict->hash_map_size - 1);
    aiv_dict_item_t *item = dict->hash_map[hash];

    while(item)
    {
        if (key_len == item->key_len && !memcmp(item->key, key, key_len))
        {
            return item->data;
        }
        item = item->next;
    }

    return NULL;
}