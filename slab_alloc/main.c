#include "header.h"

/**
 * Эти две функции вы должны использовать для аллокации
 * и освобождения памяти в этом задании. Считайте, что
 * внутри они используют buddy аллокатор с размером
 * страницы равным 4096 байтам.
 **/

/**
 * Аллоцирует участок размером 4096 * 2^order байт,
 * выровненный на границу 4096 * 2^order байт. order
 * должен быть в интервале [0; 10] (обе границы
 * включительно), т. е. вы не можете аллоцировать больше
 * 4Mb за раз.
 **/
void *alloc_slab(int order);
/**
 * Освобождает участок ранее аллоцированный с помощью
 * функции alloc_slab.
 **/
void free_slab(void *slab);

/**
 * Функция инициализации будет вызвана перед тем, как
 * использовать это кеширующий аллокатор для аллокации.
 * Параметры:
 *  - cache - структура, которую вы должны инициализировать
 *  - object_size - размер объектов, которые должен
 *    аллоцировать этот кеширующий аллокатор 
 **/
void            cache_setup(struct cache *cache, size_t object_size)
{
	cache->object_size = object_size;
	// cache->slab_order =
	// cache->slab_objects =

	cache->empty_slabs = NULL;
	cache->def_slabs = NULL;
	cache->filled_slabs = NULL;
}


/**
 * Функция освобождения будет вызвана когда работа с
 * аллокатором будет закончена. Она должна освободить
 * всю память занятую аллокатором. Проверяющая система
 * будет считать ошибкой, если не вся память будет
 * освбождена.
 **/
void cache_release(struct cache *cache)
{
	/* Реализуйте эту функцию. */
}

/**
 * Функция аллокации памяти из кеширующего аллокатора.
 * Должна возвращать указатель на участок памяти размера
 * как минимум object_size байт (см cache_setup).
 * Гарантируется, что cache указывает на корректный
 * инициализированный аллокатор.
 **/
void            *cache_alloc(struct cache *cache)
{
	t_list      *list_runner;

	/* проверяем список частично занятых slab`ов */
	list_runner = cache->def_slabs;
	while (list_runner != NULL)
	{
		if (((struct slab *)list_runner->value)->free_size != 0)
			break;
		list_runner = list_runner->next;
	}
	if (list_runner != NULL)
		return (get_object_from_def(cache, list_runner));

	/* проверяем список свободных slab`ов */
	if (cache->empty_slabs != NULL)
		return get_object_from_empty(cache);
	
	/* просим больше памяти */
	if (alloc_memory(cache) == NULL)
		return NULL;
	return get_object_from_empty(cache);
}


/**
 * Функция освобождения памяти назад в кеширующий аллокатор.
 * Гарантируется, что ptr - указатель ранее возвращенный из
 * cache_alloc.
 **/
void cache_free(struct cache *cache, void *ptr)
{
	/* Реализуйте эту функцию. */
}


/**
 * Функция должна освободить все SLAB, которые не содержат
 * занятых объектов. Если SLAB не использовался для аллокации
 * объектов (например, если вы выделяли с помощью alloc_slab
 * память для внутренних нужд вашего алгоритма), то освбождать
 * его не обязательно.
 **/
void cache_shrink(struct cache *cache)
{
	/* Реализуйте эту функцию. */
}