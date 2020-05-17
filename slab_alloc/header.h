
#ifndef HEADER_H
# define HEADER_H

#include <stdlib.h>

# define PAGE_SIZE 4096

typedef struct      s_list
{
    void            *value;
    struct s_list   *next;
    struct s_list   *prev;
}                   t_list;

struct slab
{
    t_list     *free;
    size_t      free_size;
    t_list     *busy;
    size_t      busy_size;
};

/**
 * Эта структура представляет аллокатор, вы можете менять
 * ее как вам удобно. Приведенные в ней поля и комментарии
 * просто дают общую идею того, что вам может понадобится
 * сохранить в этой структуре.
 **/
struct cache {
    t_list         *empty_slabs; /* список пустых SLAB-ов для поддержки cache_shrink */
    t_list         *def_slabs; /* список частично занятых SLAB-ов */
    t_list         *filled_slabs; /* список заполненых SLAB-ов */

    size_t          object_size; /* размер аллоцируемого объекта */
    int             slab_order; /* используемый размер SLAB-а */
    size_t          slab_objects; /* количество объектов в одном SLAB-е */ 
};

t_list              *lst_new(void *memory_block);
void                lst_add(t_list **head, t_list *new);

#endif