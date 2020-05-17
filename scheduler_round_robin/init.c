#include "header.h"

t_scheduler				*init_scheduler(int timeslice)
{
	t_scheduler			*s;

	if ((s = (t_scheduler *)malloc(sizeof(t_scheduler))) == NULL)
		return NULL;
	s->thread_queue = NULL;
	s->running_thread = NULL;
	s->blocked_thread = NULL;
	s->timeslice = timeslice;
	s->running_time_thread = 0;
	return s;
}

void					del_content_thread(void *content, size_t content_size)
{
	if (content != NULL)
	{
		((t_thread *)content)->id = 0;
		free(content);
		content = NULL;
	}
	content_size = 0;
}

void					delete_scheduler(t_scheduler **s)
{
	if (*s == NULL)
		return ;
	ft_lstdel(&((*s)->thread_queue), del_content_thread);
	(*s)->thread_queue = NULL;
	delete_thread(&((*s)->running_thread));
	(*s)->running_thread = NULL;
	ft_lstdel(&((*s)->blocked_thread), del_content_thread);
	(*s)->blocked_thread = NULL;
	(*s)->timeslice = 0;
	(*s)->running_time_thread = 0;
	free(*s);
	*s = NULL;
}

t_thread				*create_thread(int thread_id)
{
	t_thread			*t;

	if ((t = (t_thread *)malloc(sizeof(t_thread))) == NULL)
		return NULL;
	t->id = thread_id;
	return t;
}

void					delete_thread(t_thread **t)
{
	if (*t == NULL)
		return ;
	(*t)->id = 0;
	free(*t);
	*t = NULL;
}
