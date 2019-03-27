#include "../includes/allocator.h"

void    *mem_realloc(void *addr, size_t size)
{
    unsigned int i;
    unsigned int block_size;
    void *data;

    block_size = (addr - (void *)g_pages - PAGE_SIZE_DATA * g_page_count);
    i = block_size / PAGE_SIZE;
    block_size = (g_pages[i].size != 0) ?\
    g_pages[i].size * PAGE_SIZE : PAGE_SIZE / 2;
    data = mem_alloc(size);
    memmove(data, addr, block_size > size ? size : block_size);
    mem_free(addr);
    return (data);
}