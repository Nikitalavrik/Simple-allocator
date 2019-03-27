#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <string.h>

# define VIRTUAL_SIZE   4288
# define PAGE_SIZE      512
# define PAGE_SIZE_DATA 24
# define UNDEFINED      -1
# define IS_FREE        0
# define IS_DIV         1
# define IS_INBLOCK     2
# define IS_BUSY        5
# define IS_MBUSY		6

typedef struct  s_pages
{
    void    *addr;
    char    state;
    size_t  size;
}               t_pages;

void    	init_mem(size_t size);
void     	*find_free_small(size_t size);
void    	*find_free_big(size_t size);
void    	*mem_alloc(size_t size);
void   		mem_dump();
void    	mem_free(void * addr);
void    	*mem_realloc(void *addr, size_t size);
void    	fill_state(unsigned int i, unsigned int n, int state);

void            *g_mem;
unsigned int    g_page_count;
t_pages         *g_pages;

#endif