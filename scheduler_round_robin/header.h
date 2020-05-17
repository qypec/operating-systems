#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_thread
{
	int					id;
}						t_thread;

typedef struct			s_scheduler
{
	t_list				*thread_queue;
	t_thread			*running_thread;
	t_list				*blocked_thread;
	int					timeslice;
	int					running_time_thread;
}						t_scheduler;

t_scheduler				*g_scheduler;

t_scheduler				*init_scheduler(int timeslice);
void					delete_scheduler(t_scheduler **s);
t_thread				*create_thread(int thread_id);
void					delete_thread(t_thread **t);

void					del_content_thread(void *content, size_t content_size);

void					ft_lstdelthis(t_list **alst, size_t lstnum, \
											void (*del)(void *, size_t));
t_list					*ft_lstnew(void *content, size_t content_size);
void					ft_lstpushback(t_list **alst, t_list *neww);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, \
							void (*del)(void *, size_t));
void					ft_lstdelhead(t_list **alst, \
							void (*del)(void *, size_t));
t_list					*ft_extracthead(t_list **lst);

#endif