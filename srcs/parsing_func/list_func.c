/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:16:23 by sseo              #+#    #+#             */
/*   Updated: 2021/02/02 20:16:24 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		list = list->next;
		free(current->data);
		free(current);
	}
}

void		*edit_list4redirection(t_list **p_first_elem, t_list *before)
{
	void		*out_data;
	t_list		*current;
	t_list		*after;
	int			cnt;

	cnt = 0;
	if (!before)
		current = *p_first_elem;
	else
		current = before->next;
	after = current->next;
	if (!before)
		*p_first_elem = after->next;
	else
		before->next = after->next;
	out_data = after->data;
	free(current->data);
	free(current);
	free(after);
	return (out_data);
}
