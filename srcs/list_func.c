#include "minishell.h"

int			add_data(t_list **plist, void **data)
{
	t_list		*new;
	t_list		*list;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (1);
	new->data = *data;
	new->next = 0;
	list = *plist;
	if (!list)
		*plist = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	return (0);
}

void		free_list(t_list *list)
{
	t_list		*current;

	while (list)
	{
		current = list;
		list=list->next;
		free(current->data);
		free(current);
	}
}
