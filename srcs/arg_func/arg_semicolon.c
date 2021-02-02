/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_semicolon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:30:34 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 19:44:40 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		arg_semicolon(t_list **p_first_elem, t_list *target, \
			int *receiver, int *sender)
{
	t_list	*current;

	current = *p_first_elem;
	if ((execute_command(current, target, receiver, sender)) != 2)
	{
		receiver[0] = -1;
		sender[0] = -1;
		current = target;
		target = target->next;
		free(current->data);
		free(current);
		handle_command(&target, receiver, sender);
	}
}
