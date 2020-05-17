
# include "header.h"

void					ft_lstdelthis(t_list **alst, size_t lstnum, \
											void (*del)(void *, size_t))
{
	while (*alst != NULL && lstnum)
	{
		alst = &(*alst)->next;
		lstnum--;
	}
	if (lstnum == 0 && *alst != NULL)
		ft_lstdelhead(alst, del);
}

t_list					*ft_extracthead(t_list **lst)
{
	t_list				*tmp;

	if (*lst == NULL)
		return NULL;
	tmp = *lst;
	*lst = (*lst)->next;
	tmp->next = NULL;
	return tmp;
}

t_list					*ft_lstnew(void *content, size_t content_size)
{
	t_list				*list;

	if ((list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	list->content = content;
	if (list->content != NULL)
		list->content_size = content_size;
	else
		list->content_size = 0;
	list->next = NULL;
	return (list);
}

void					ft_lstpushback(t_list **alst, t_list *neww)
{
	if (neww == NULL)
		return ;
	while (*alst != NULL)
		alst = &(*alst)->next;
	*alst = neww;
}

void					ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (*alst == NULL)
		return ;
	del((*alst)->content, (*alst)->content_size);
	(*alst)->next = NULL;
	free(*alst);
	*alst = NULL;
}


void					ft_lstdelhead(t_list **alst, void (*del)(void *, size_t))
{
	t_list				*tmp;

	tmp = (*alst)->next;
	ft_lstdelone(alst, del);
	*alst = tmp;
}

void					ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	while (*alst != NULL)
		ft_lstdelhead(alst, del);
}
