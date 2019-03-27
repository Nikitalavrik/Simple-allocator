#include "../includes/allocator.h"

void    *mem_alloc(size_t size)
{
    if (size <= PAGE_SIZE)
        return (find_free_small(size));
    else
        return (find_free_big(size));
    return (NULL);
}