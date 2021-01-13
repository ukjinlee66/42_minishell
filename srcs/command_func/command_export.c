/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:38:22 by youlee            #+#    #+#             */
/*   Updated: 2021/01/13 16:54:37 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	command_export(char **argv, int *receiver, int *sender)
{
	int	idx;
	
	idx = 0;
	while (soenvl[idx])
	{
		if (soenvl[idx][0] == '\0') 
			break;
		write(1, soenvl[idx], ft_strlen(soenvl[idx]));
		write(1, "\n", 1);
		idx++;
	}
}
