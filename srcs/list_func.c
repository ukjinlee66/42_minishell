#include "minishell.h"

int			add_data(t_list **p_list, void **p_data)
{
	t_list		*new;
	t_list		*list;
	void		*data;

	list = *p_list;
	data = *p_data;
	if (data == 0)
		return (0);
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (1);
	new->data = data;
	new->next = 0;
	if (!list)
		*p_list = new;
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

t_list		*free_first_elem(t_list *list)
{
	t_list		*out;

	if (!list)
		return (0);
	out = list->next;
	free(list->data);
	free(list);
	return (out);
}
