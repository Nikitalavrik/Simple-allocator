#include "../includes/allocator.h"

void    mem_free(void * addr)
{
    unsigned int i;
    unsigned int block_size;
    unsigned int prev_state;

    block_size = (addr - (void *)g_pages - PAGE_SIZE_DATA * g_page_count);
    i = block_size / PAGE_SIZE;
    prev_state = g_pages[i].state;
    if (prev_state == IS_MBUSY || prev_state == IS_DIV)
        g_pages[i].state = (prev_state == IS_MBUSY) ? IS_DIV : IS_FREE;
    if (prev_state == IS_BUSY)
        g_pages[i].state = IS_FREE;
    if (prev_state == IS_INBLOCK)
        fill_state(i, i + g_pages[i].size, IS_FREE);
    block_size = (g_pages[i].size != 0) ?\
            g_pages[i].size * PAGE_SIZE : PAGE_SIZE / 2;
    g_pages[i].size = 0;
    bzero(addr, block_size);
    addr = NULL;
}