#include "../includes/allocator.h"

void    mem_dump()
{
    unsigned int i;
    unsigned int tmp;

    for (i = 0; i < g_page_count; i++)
    {
        printf("page = %i state = %3i\n", i, g_pages[i].state);
        printf("data = %8s\n", (char *)((void *)g_pages +
        (PAGE_SIZE_DATA * g_page_count + i * PAGE_SIZE)));
        if (g_pages[i].state == IS_MBUSY || g_pages[i].state == IS_DIV)
            printf("data = %8s\n", (char *)((void *)g_pages +
            (PAGE_SIZE_DATA * g_page_count + i * PAGE_SIZE + PAGE_SIZE / 2)));
        printf("-----------------------------\n");
    }

    printf("|||||||||||||||||||||||||||||||\n");
}

int     main(void)
{
    void    *data;
    void    *data2;
    void    *data3;
    void    *data4;

    init_mem(VIRTUAL_SIZE);
    printf("g_mem = %p\n", g_pages);
    data = mem_alloc(200);
    memmove(data, "kek", 3);
    data2 = mem_alloc(200);
    memmove(data2, "cmp", 3);
    data3 = mem_alloc(1000);
    memmove(data3, "ter", 3);
    // data4 = mem_alloc(500);
    // memmove(data4, "lol", 3);
    // memmove(data3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    // aaaaaaaaaaaaa", 517);
    mem_dump();
    // mem_free(data);
    // mem_free(data2);
    // mem_free(data4);
    // mem_realloc(data2, 1500);
    // mem_realloc(data, 500);
    mem_realloc(data3, 500);
    mem_dump();
    return (0);
}