/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:30:17 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 19:08:06 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_sender(int *sender, int new_pipe)
{
	if (sender[0] != -1)
		close(sender[0]);
	sender[0] = new_pipe;
	sender[1] = -1;
}

void	control_open_error(int eno, t_list *first_elem)
{
	char		*str;

	str = strerror(eno);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free_list(first_elem);
}
