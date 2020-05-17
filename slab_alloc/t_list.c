#include "header.h"

t_list              *lst_new(void *memory_block)
{
    t_list          *new;

    new = (t_list *)memory_block;
    new->next = NULL;
    new->prev = NULL;
    new->value = memory_block + sizeof(t_list); // указатель на область памяти размером object_size
    return new;
}

void                lst_add(t_list **head, t_list *new)
{
    t_list          *tmp;

    if (*head != NULL)
    {
        new->next = *head;
        new->prev = NULL;
        (*head)->prev = new;   
    }
    head = &new;
}
