#include "../includes/allocator.h"

void    init_mem(size_t size)
{
    unsigned int i;

    i = 0;
    g_pages = malloc(size);
    g_page_count = size / (PAGE_SIZE + PAGE_SIZE_DATA);
    while (i < g_page_count)
    {
        g_pages[i].size = 0;
        g_pages[i].state = IS_FREE;
        i++;
    }
}

void    *find_free_small(size_t size)
{
    unsigned int    i;
    void            *addr;

    i = 0;
    for (i = 0; i < g_page_count; i++)
    {
        if (g_pages[i].state == IS_FREE ||\
        (g_pages[i].state == IS_DIV && size < PAGE_SIZE / 2))
        {
            addr = (void *)g_pages + (PAGE_SIZE_DATA * g_page_count + i * PAGE_SIZE +\
            ((g_pages[i].state == IS_DIV) ? PAGE_SIZE / 2 : 0));
            if (size > PAGE_SIZE / 2)
                g_pages[i].state = IS_BUSY;
            else
                g_pages[i].state = (g_pages[i].state == IS_DIV) ? IS_MBUSY : IS_DIV;
            g_pages[i].size = size > PAGE_SIZE / 2 ? 1 : 0;
            return (addr);
        }
    }
    return (NULL);
}

void    fill_state(unsigned int i, unsigned int n, int state)
{
    while (i < n)
        g_pages[i++].state = state;
}

void    *find_free_big(size_t size)
{
    unsigned int i;
    unsigned int need_page;
    unsigned int count;
    unsigned int max_count;
    unsigned int fail_i;
    void         *addr;

    addr = NULL;
    count = 0;
    max_count = 0;
    need_page = (double)size / PAGE_SIZE + 0.5;
    for (i = 0; i < g_page_count; i++)
    {
        if (g_pages[i].state == IS_FREE)
        {
            fail_i = ++count > max_count ? i : fail_i;
            max_count = count > max_count ? count : max_count;
            if (count == need_page)
                break ;
        }
        else
            count = 0;
    }
    if (!fail_i || !max_count)
        return (NULL);
    fill_state(fail_i - max_count + 1, fail_i + 1, IS_INBLOCK);
    g_pages[fail_i - max_count + 1].size = need_page;
    return ((void *)g_pages + (PAGE_SIZE_DATA * g_page_count +\
            (fail_i - max_count + 1) * PAGE_SIZE));
}
