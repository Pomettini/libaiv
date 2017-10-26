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