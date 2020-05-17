#include "header.h"

/**
 * Функция создания slab`а. Делит memory_block, размера memory_size, полученный от аллокатора,
 * на кусочки по cache->object_size памяти. Объединяет их в список.
 * Возвращает указатель на slab. 
 * Метаданные slab`a лежат в начале memory_block, занимают sizeof(struct slab) памяти.
 * Метаданные двусвязных списков лежат перед каждым кусочком, занимают sizeof(t_list) памяти.
 **/ 
struct slab         *create_slab(struct cache *cache, void *memory_block, size_t memory_size)
{
	struct slab     *new_slab;
	size_t          filled_size;

/* инициализация */
	new_slab = (struct slab *)memory_block;
	new_slab->free = NULL;
	new_slab->free_size = 0;
	new_slab->busy = NULL;
	new_slab->busy_size = 0;

/* разделение блока памяти на кусочки */
/* формирование двусвязного списка из кусочков */
	filled_size = sizeof(struct slab);
	while (filled_size + (sizeof(t_list) + cache->object_size) < memory_size)
	{
		lst_add(&(new_slab->free), lst_new(memory_block + filled_size));
		new_slab->free_size++;
		filled_size += sizeof(t_list) + cache->object_size; // шаг по памяти
	}
	if (new_slab->free == NULL)
		return NULL;
	return new_slab;
}

/* Функция получает память и распределяет ее по slab`ам */
void                *alloc_memory(struct cache *cache)
{
	void            *memory_block;
	size_t          memory_size;
	size_t          filled_size;

	memory_block = alloc_slab(cache->slab_order);
	memory_size = cache->slab_order * PAGE_SIZE;
	filled_size = 0;
	while (filled_size + (sizeof(t_list) + cache->slab_objects * cache->object_size) < memory_size)
	{
		lst_add(&(cache->empty_slabs), lst_new(memory_block + filled_size));
		filled_size += sizeof(t_list);
		cache->empty_slabs->value = create_slab(cache, memory_block + filled_size, \
			cache->slab_objects * cache->object_size);
		if (cache->empty_slabs->value == NULL)
			return NULL;
		filled_size += cache->slab_objects * cache->object_size;
	}
}

// void				move_slab(t_list *from, t_list *to)
// {
// 	struct slab		*roaming;

	
// }