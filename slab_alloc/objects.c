#include "header.h"

/* Функция перемещает внутри slab`a объект из списка свободных в список занятых. */
void				occupy_object(struct slab *slab, t_list *object)
{
	if (object->prev == NULL)
		slab->free = object->next;
	else
		object->prev->next = object->next;
	if (object->next != NULL)
		object->next->prev = object->prev;
	slab->free_size--;
	
	slab->busy->prev = object;
	object->next = slab->busy;
	object->prev = NULL;
	slab->busy_size++;
}

/**
 * Функция возвращает указатель на свободный кусочек памяти из пустого slab`a.
 * Перемещает этот slab из списка пустых либо в список частично заполненных, либо
 * в список полностью заполненных.
 **/
void                *get_object_from_empty(struct cache *cache)
{
	void			*object; // указатель на нужный кусок памяти
	struct slab		*first_empty_slab;

	first_empty_slab = (struct slab *)cache->empty_slabs->value;
	object = first_empty_slab->free->value;
	occupy_object(first_empty_slab, first_empty_slab->free);

	if (first_empty_slab->free_size != 0)
		move_slab(cache->empty_slabs, cache->def_slabs);
	else
		move_slab(cache->empty_slabs, cache->filled_slabs);
	return object;
}